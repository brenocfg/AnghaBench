#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  keysym; } ;
struct TYPE_5__ {int type; TYPE_1__ key; } ;
typedef  TYPE_2__ SDL_Event ;

/* Variables and functions */
#define  SDL_KEYDOWN 129 
 scalar_t__ SDL_PollEvent (TYPE_2__*) ; 
#define  SDL_QUIT 128 
 int /*<<< orphan*/  handle_key_down (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  quit_tutorial (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void process_events( void )
{
    /* Our SDL event placeholder. */
    SDL_Event event;
    
    /* Grab all the events off the queue. */
    while( SDL_PollEvent( &event ) ) {
        
        switch( event.type ) {
            case SDL_KEYDOWN:
                /* Handle key presses. */
                handle_key_down( &event.key.keysym );
                break;
            case SDL_QUIT:
                /* Handle quit requests (like Ctrl-c). */
                quit_tutorial( 0 );
                break;
        }
        
    }
    
}