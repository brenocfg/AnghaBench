#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int r; int g; int b; scalar_t__ unused; } ;
struct TYPE_5__ {int member_0; int member_1; int member_2; int member_3; } ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  TYPE_1__ SDL_Rect ;
typedef  TYPE_2__ SDL_Color ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FillRect (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int SDL_HWPALETTE ; 
 int SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SetColors (int /*<<< orphan*/ *,TYPE_2__*,int,int) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int,int,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 

int main() {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(600, 400, 8, SDL_HWSURFACE | SDL_HWPALETTE);

  //initialize sdl palette
  //with red green and blue
  //colors
  SDL_Color pal[3];
  pal[0].r = 255;
  pal[0].g = 0;
  pal[0].b = 0;
  pal[0].unused = 0;

  pal[1].r = 0;
  pal[1].g = 255;
  pal[1].b = 0;
  pal[1].unused = 0;

  pal[2].r = 0;
  pal[2].g = 0;
  pal[2].b = 255;
  pal[2].unused = 0;

  SDL_SetColors(screen, pal, 0, 3);

  SDL_FillRect(screen, NULL, 0);

  {
    SDL_Rect rect = { 300, 0, 300, 200 };
    SDL_FillRect(screen, &rect, 1);
  }

  {
    SDL_Rect rect = { 0, 200, 600, 200 };
    SDL_FillRect(screen, &rect, 2);
  }

  //changing green color
  //to yellow
  pal[1].r = 255;
  SDL_SetColors(screen, &pal[1], 1, 1);

  {
    SDL_Rect rect = { 300, 200, 300, 200 };
    SDL_FillRect(screen, &rect, 1);
  }

  printf("you should see red, blue and yellow rectangles\n");

  SDL_Quit();

  return 0;
}