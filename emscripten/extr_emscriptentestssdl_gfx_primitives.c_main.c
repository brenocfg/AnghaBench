#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ type; } ;
typedef  int /*<<< orphan*/  SDL_Surface ;
typedef  TYPE_1__ SDL_Event ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_Delay (int) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 scalar_t__ SDL_PollEvent (TYPE_1__*) ; 
 scalar_t__ SDL_QUIT ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SaveBMP (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * SDL_SetVideoMode (int const,int const,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UpdateRect (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  boxColor (int /*<<< orphan*/ *,int,int,int const,int const,int) ; 
 int /*<<< orphan*/  boxRGBA (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  ellipseColor (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  filledEllipseColor (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  filledEllipseRGBA (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  lineColor (int /*<<< orphan*/ *,int,int,int,int,int) ; 
 int /*<<< orphan*/  lineRGBA (int /*<<< orphan*/ *,int,int,int,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rectangleColor (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  rectangleRGBA (int /*<<< orphan*/ *,int,int,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

int main(int argc, char **argv) {
    SDL_Init(SDL_INIT_VIDEO);

    const int width = 400;
    const int height = 400;
    SDL_Surface *screen = SDL_SetVideoMode(width, height, 32, SDL_SWSURFACE);
    boxColor(screen, 0, 0, width, height, 0xff);

    boxColor(screen, 0, 0, 98, 98, 0xff0000ff);
    boxRGBA(screen, 100, 0, 198, 98, 0, 0, 0xff, 0xff);
    // check that the x2 > x1 case is handled correctly
    boxColor(screen, 298, 98, 200, 0, 0x00ff00ff);
    boxColor(screen, 398, 98, 300, 0, 0xff0000ff);

    rectangleColor(screen, 0, 100, 98, 198, 0x000ffff);
    rectangleRGBA(screen, 100, 100, 198, 198, 0xff, 0, 0, 0xff);

    ellipseColor(screen, 300, 150, 99, 49, 0x00ff00ff);
    filledEllipseColor(screen, 100, 250, 99, 49, 0x00ff00ff);
    filledEllipseRGBA(screen, 250, 300, 49, 99, 0, 0, 0xff, 0xff);

    lineColor(screen, 300, 200, 400, 300, 0x00ff00ff);
    lineRGBA(screen, 300, 300, 400, 400, 0, 0xff, 0, 0xff);

    SDL_UpdateRect(screen, 0, 0, 0, 0);

#ifndef __EMSCRIPTEN__
    SDL_Event evt;
    SDL_SaveBMP(screen, "native_output.bmp");
    while (1) {
       if (SDL_PollEvent(&evt) != 0 && evt.type == SDL_QUIT) break;
       SDL_Delay(33);
    }
#endif

    SDL_Quit();

    return 1;
}