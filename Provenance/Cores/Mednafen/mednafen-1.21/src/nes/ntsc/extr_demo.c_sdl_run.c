#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int w; int h; } ;
struct TYPE_6__ {scalar_t__ sym; } ;
struct TYPE_7__ {TYPE_1__ keysym; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_2__ key; } ;
typedef  TYPE_3__ SDL_Event ;

/* Variables and functions */
 scalar_t__ SDLK_ESCAPE ; 
 scalar_t__ SDLK_q ; 
 int /*<<< orphan*/  SDL_Delay (unsigned long) ; 
 int /*<<< orphan*/  SDL_GetMouseState (int*,int*) ; 
 unsigned long SDL_GetTicks () ; 
 TYPE_5__* SDL_GetVideoSurface () ; 
 scalar_t__ SDL_KEYDOWN ; 
 scalar_t__ SDL_MOUSEBUTTONDOWN ; 
 scalar_t__ SDL_MOUSEMOTION ; 
 scalar_t__ SDL_PollEvent (TYPE_3__*) ; 
 scalar_t__ SDL_QUIT ; 
 scalar_t__ key_pressed ; 
 int mouse_moved ; 
 int mouse_x ; 
 int mouse_y ; 
 unsigned long next_time ; 

int sdl_run()
{
	SDL_Event e;
	
	/* limit to 60 calls per second */
	unsigned long start = SDL_GetTicks();
	if ( start < next_time && next_time - start > 10 )
		SDL_Delay( next_time - start );
	while ( SDL_GetTicks() < next_time ) { }
	next_time = start + 1000 / 60;
	
	mouse_moved = 0;
	key_pressed = 0;
	
	while ( SDL_PollEvent( &e ) )
	{
		if ( e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_QUIT )
			return 0;
		
		if ( e.type == SDL_KEYDOWN )
		{
			if ( e.key.keysym.sym == SDLK_ESCAPE || e.key.keysym.sym == SDLK_q )
				return 0;
			key_pressed = e.key.keysym.sym;
		}
		
		if ( e.type == SDL_MOUSEMOTION )
		{
			int x, y;
			SDL_GetMouseState( &x, &y );
			mouse_moved = 1;
			mouse_x = x / (float) (SDL_GetVideoSurface()->w - 1);
			mouse_y = 1 - y / (float) (SDL_GetVideoSurface()->h - 1);
		}
	}
	return 1;
}