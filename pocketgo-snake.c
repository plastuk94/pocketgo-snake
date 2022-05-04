#include <SDL.h>
#include <stdio.h>

#define BTN_UP		SDLK_UP
#define BTN_DOWN 	SDLK_DOWN
#define BTN_LEFT 	SDLK_LEFT
#define BTN_RIGHT 	SDLK_RIGHT
#define BTN_A		SDLK_LALT
#define BTN_B 		SDLK_LCTRL
#define BTN_X		SDLK_LSHIFT
#define BTN_Y		SDLK_SPACE
#define BTN_START	SDLK_RETURN
#define BTN_SELECT	SDLK_ESCAPE
#define BTN_RESET	SDLK_RCTRL
#define WIDTH		320
#define HEIGHT		240
#define BLOB_WIDTH	10
#define BLOB_HEIGHT	10


void draw(int x, int y, SDL_Surface* screen) {

	SDL_Rect blobRect;
	blobRect.x = x;
	blobRect.y = y;
	blobRect.w = BLOB_WIDTH;
	blobRect.h = BLOB_HEIGHT;
	SDL_FillRect(screen, NULL, 0x00000000);		/* Blank the screen */
	SDL_FillRect(screen, &blobRect, 0xffffff00);	/* Draw the blob */ 
	SDL_UpdateRect(screen, 0, 0, 0, 0);		/* Update the screen */

}

int main(int argc, char *argv[]) {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Failed to initialize SDL!");
	}

	SDL_Surface* screen = SDL_SetVideoMode(WIDTH, HEIGHT, 0, 0);
	SDL_SetClipRect(screen, NULL);

	int quit = 0;

	int xVel = 0, yVel = 0, xPos = 0, yPos = 0;
	
	SDL_Event event;
	while (!quit) {
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					quit = 1;
					break;
				case SDL_KEYDOWN:
					switch (event.key.keysym.sym) {
						case BTN_UP:
							yVel = -1;
							break;
						case BTN_DOWN:
							yVel = 1;
							break;
						case BTN_LEFT:
							xVel = -1;
							break;
						case BTN_RIGHT:
							xVel = 1;
							break;
						case BTN_SELECT:
							quit = 1;
							break;
					}
					break;
			}

		}

		xPos = xPos + xVel;
		yPos = yPos + yVel;

		if ((xPos == 0) || (xPos == (WIDTH - BLOB_WIDTH))) {
			xVel = 0;
		}
		if ((yPos == 0) || (yPos == (HEIGHT - BLOB_HEIGHT))) {
			yVel = 0;
		}
		if (yPos < 0) {
			yPos = 0;
		}
		if (yPos > (HEIGHT - BLOB_HEIGHT)) {
			yPos = (HEIGHT - BLOB_HEIGHT);
		}
		if (xPos < 0) {
			xPos = 0;
		}
		if (xPos > (WIDTH - BLOB_WIDTH)) {
			xPos = (WIDTH - BLOB_WIDTH);
		}
		draw(xPos, yPos, screen);
	}

	SDL_FreeSurface(screen);
	SDL_Quit();

	return 0;
}
									
