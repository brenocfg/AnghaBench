#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_13__ {int member_2; int member_3; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_Surface ;
typedef  TYPE_2__ SDL_Rect ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_BlitSurface (TYPE_1__*,TYPE_2__*,TYPE_1__*,TYPE_2__*) ; 
 TYPE_1__* SDL_CreateRGBSurfaceFrom (int*,int,int,int,int,int,int,int,int) ; 
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_HWSURFACE ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_MapRGB (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UpdateRect (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int height ; 
 int /*<<< orphan*/  printf (char*) ; 
 int width ; 

int main() {

  uint8_t pixels[width * height * 4];
  uint8_t *end = pixels + width * height * 4;
  uint8_t *pixel = pixels;
  SDL_Rect rect = {0, 0, width, height};

  while (pixel != end) {
  	*pixel = (pixel - pixels) * 256 / (width * height * 4);
  	pixel++;
  }

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_HWSURFACE);
  SDL_Surface *image = SDL_CreateRGBSurfaceFrom(pixels, width, height, 32, width * 4, 
    0x000000ff, 
    0x0000ff00, 
    0x00ff0000, 
    0xff000000);

  SDL_FillRect(screen, &rect, SDL_MapRGB(screen->format, 255, 0, 0));
  SDL_BlitSurface(image, &rect, screen, &rect);
  SDL_UpdateRect(screen, 0, 0, width, height);

  printf("There should be a red to white gradient\n");

  SDL_Quit();

  return 0;
}