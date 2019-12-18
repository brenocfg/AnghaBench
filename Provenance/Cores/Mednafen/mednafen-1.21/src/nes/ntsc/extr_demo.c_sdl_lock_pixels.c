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
struct TYPE_3__ {scalar_t__ pixels; int /*<<< orphan*/  pitch; } ;

/* Variables and functions */
 scalar_t__ SDL_LockSurface (TYPE_1__*) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 int /*<<< orphan*/  sdl_pitch ; 
 unsigned char* sdl_pixels ; 
 TYPE_1__* surface ; 

void sdl_lock_pixels()
{
	if ( SDL_LockSurface( surface ) < 0 )
		fatal_error( "Couldn't lock surface" );
	sdl_pitch = surface->pitch;
	sdl_pixels = (unsigned char*) surface->pixels;
}