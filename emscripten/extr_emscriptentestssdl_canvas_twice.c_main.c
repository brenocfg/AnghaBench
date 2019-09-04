#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ pixels; int /*<<< orphan*/  format; } ;
typedef  TYPE_1__ SDL_Surface ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_FillRect (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Flip (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 int /*<<< orphan*/  SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_LockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  SDL_MapRGBA (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 TYPE_1__* SDL_SetVideoMode (int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (TYPE_1__*) ; 

int main(int argc, char **argv) {
  SDL_Init(SDL_INIT_VIDEO);
  SDL_Surface *screen = SDL_SetVideoMode(40, 40, 32, SDL_SWSURFACE);

  SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 0xff, 0, 0, 0xff));
  SDL_LockSurface(screen);
  *((int*)screen->pixels + 95) = 0;
  SDL_UnlockSurface(screen);

  SDL_FillRect(screen, NULL, SDL_MapRGBA(screen->format, 0, 0xff, 0, 0xff)); // wipe out previous pixel and fill
  SDL_LockSurface(screen);
  *((int*)screen->pixels + 205) = 0;
  SDL_UnlockSurface(screen);

  SDL_Flip(screen);

  return 0;
}