#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int r; int g; int b; int a; } ;
struct TYPE_12__ {int member_0; int member_1; int member_2; int member_3; } ;
struct TYPE_11__ {TYPE_1__* format; } ;
struct TYPE_10__ {int /*<<< orphan*/  palette; } ;
typedef  int /*<<< orphan*/  SDL_Window ;
typedef  int /*<<< orphan*/  SDL_Texture ;
typedef  TYPE_2__ SDL_Surface ;
typedef  int /*<<< orphan*/  SDL_Renderer ;
typedef  TYPE_3__ SDL_Rect ;
typedef  TYPE_4__ SDL_Color ;

/* Variables and functions */
 TYPE_2__* SDL_CreateRGBSurface (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * SDL_CreateTextureFromSurface (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  SDL_CreateWindowAndRenderer (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  SDL_FillRect (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_RenderClear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderCopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_RenderPresent (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SDL_SetPaletteColors (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *window;
  SDL_Renderer *renderer;

  SDL_CreateWindowAndRenderer(600, 400, 0, &window, &renderer);

  SDL_Surface *screen = SDL_CreateRGBSurface(0, 600, 400, 8, 0, 0, 0, 0);

  //initialize sdl palette
  //with red green and blue
  //colors
  SDL_Color pal[4];
  pal[0].r = 255;
  pal[0].g = 0;
  pal[0].b = 0;
  pal[0].a = 255;

  pal[1].r = 0;
  pal[1].g = 255;
  pal[1].b = 0;
  pal[1].a = 255;

  pal[2].r = 0;
  pal[2].g = 0;
  pal[2].b = 255;
  pal[2].a = 255;

  pal[3].r = 255;
  pal[3].g = 255;
  pal[3].b = 0;
  pal[3].a = 255;

  SDL_SetPaletteColors(screen->format->palette, pal, 0, 4);

  SDL_FillRect(screen, NULL, 0);

  {
    SDL_Rect rect = { 300, 0, 300, 200 };
    SDL_FillRect(screen, &rect, 1);
  }

  {
    SDL_Rect rect = { 0, 200, 600, 200 };
    SDL_FillRect(screen, &rect, 2);
  }

  {
    SDL_Rect rect = { 300, 200, 300, 200 };
    SDL_FillRect(screen, &rect, 3);
  }

  SDL_Texture *screenTexture = SDL_CreateTextureFromSurface(renderer, screen);
  SDL_RenderClear(renderer);
  SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
  SDL_RenderPresent(renderer);

  printf("you should see red, blue and yellow rectangles\n");

  // Don't quit - we need to reftest the canvas! SDL_Quit();

  return 0;
}