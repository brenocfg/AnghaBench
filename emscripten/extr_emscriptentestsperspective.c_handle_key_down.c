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
struct TYPE_3__ {int sym; } ;
typedef  TYPE_1__ SDL_keysym ;

/* Variables and functions */
#define  SDLK_ESCAPE 129 
#define  SDLK_SPACE 128 
 int /*<<< orphan*/  quit_tutorial (int /*<<< orphan*/ ) ; 
 int should_rotate ; 

__attribute__((used)) static void handle_key_down( SDL_keysym* keysym )
{
    
    /*
     * We're only interested if 'Esc' has
     * been presssed.
     *
     * EXERCISE:
     * Handle the arrow keys and have that change the
     * viewing position/angle.
     */
    switch( keysym->sym ) {
        case SDLK_ESCAPE:
            quit_tutorial( 0 );
            break;
        case SDLK_SPACE:
            should_rotate = !should_rotate;
            break;
        default:
            break;
    }
    
}