#include <SDL2/SDL.h>
#include <SDL2/SDL_surface.h>
#include <SDL2/SDL_video.h>
#include <stdio.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

// Startup up SDL and creates window
bool init();

// Loads media
bool loadMedia();

// Free the stuff and shut down SDL
void close();

// Window on which we will render
SDL_Window *gWindow = NULL;

// Surface inside the window
SDL_Surface *gScreenSurface = NULL;

// Image that will be shown on the screen
SDL_Surface *gXOut = NULL;

int main() {
  if (!init()) {
    printf("Failed to initialize");
  } else {
    if (!loadMedia()) {
      printf("failed to load media");
    } else {
      bool quit = false;
      SDL_Event e;
      while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
          if (e.type == SDL_QUIT) {
            quit = true;
          }
        }
        SDL_BlitSurface(gXOut, NULL, gScreenSurface, NULL);
        SDL_UpdateWindowSurface(gWindow);
      }
    }
  }
  close();
  return 0;
}

bool init() {
  bool success = true;
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL cannot be initialized! Error: %s\n", SDL_GetError());
    success = false;
  } else {
    gWindow = SDL_CreateWindow("Event Demo", SDL_WINDOWPOS_UNDEFINED,
                               SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH,
                               SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (gWindow == NULL) {
      printf("Window could not be created! Error%s\n", SDL_GetError());
      success = false;
    } else {
      gScreenSurface = SDL_GetWindowSurface(gWindow);
    }
  }
  return success;
}

bool loadMedia() {
  bool success = true;
  gXOut = SDL_LoadBMP("x.bmp");
  if (gXOut == NULL) {
    printf("Unable to load image! Error: %s\n", SDL_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_FreeSurface(gXOut);
  gXOut = NULL;

  SDL_FreeSurface(gScreenSurface);
  gScreenSurface = NULL;

  SDL_DestroyWindow(gWindow);
  gWindow = NULL;

  SDL_Quit();
}
