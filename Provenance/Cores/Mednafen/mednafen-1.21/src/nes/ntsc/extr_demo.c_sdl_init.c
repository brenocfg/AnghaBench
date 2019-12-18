#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int w; int h; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_CreateRGBSurface (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_INIT_VIDEO ; 
 scalar_t__ SDL_Init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SDL_Quit ; 
 int /*<<< orphan*/  SDL_SWSURFACE ; 
 int /*<<< orphan*/  SDL_SetVideoMode (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atexit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fatal_error (char*) ; 
 TYPE_1__ rect ; 
 int /*<<< orphan*/  screen ; 
 int /*<<< orphan*/  surface ; 

void sdl_init( int width, int height, int depth )
{
	rect.w = width;
	rect.h = height;
	
	if ( SDL_Init( SDL_INIT_VIDEO ) < 0 )
		fatal_error( "SDL initialization failed" );
	atexit( SDL_Quit );
	
	screen = SDL_SetVideoMode( width, height, 0, 0 );
	surface = SDL_CreateRGBSurface( SDL_SWSURFACE, width, height, depth, 0, 0, 0, 0 );
	if ( !screen || !surface )
		fatal_error( "SDL initialization failed" );
}