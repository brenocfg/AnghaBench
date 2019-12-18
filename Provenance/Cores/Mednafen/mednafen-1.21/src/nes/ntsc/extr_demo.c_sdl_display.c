#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 scalar_t__ SDL_BlitSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ SDL_Flip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_UnlockSurface (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  rect ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/  surface ; 

void sdl_display()
{
	SDL_UnlockSurface( surface );
	if ( SDL_BlitSurface( surface, &rect, screen, &rect ) < 0 || SDL_Flip( screen ) < 0 )
		fatal_error( "SDL blit failed" );
}