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
struct TYPE_3__ {int /*<<< orphan*/ * pixels; } ;
typedef  TYPE_1__ SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit () ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int main(int argc, char** argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(256, 256, 32, SDL_SWSURFACE);

  // pixels should always be initialized for software surfaces,
  // without having to call SDL_LockSurface / SDL_UnlockSurface
  assert(screen->pixels != NULL);

  SDL_Quit();

#ifdef __EMSCRIPTEN__
  REPORT_RESULT(1);
#endif

  return 0;
}