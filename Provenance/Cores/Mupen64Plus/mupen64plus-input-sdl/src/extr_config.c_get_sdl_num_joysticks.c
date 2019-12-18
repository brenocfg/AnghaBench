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
 int /*<<< orphan*/  DebugMessage (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M64MSG_ERROR ; 
 int /*<<< orphan*/  SDL_GetError () ; 
 int /*<<< orphan*/  SDL_INIT_JOYSTICK ; 
 int SDL_InitSubSystem (int /*<<< orphan*/ ) ; 
 int SDL_NumJoysticks () ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int SDL_WasInit (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_sdl_num_joysticks(void)
{
    int numJoysticks = 0;
    int joyWasInit = SDL_WasInit(SDL_INIT_JOYSTICK);
    
    /* initialize the joystick subsystem if necessary */
    if (!joyWasInit)
        if (SDL_InitSubSystem(SDL_INIT_JOYSTICK) == -1)
        {
            DebugMessage(M64MSG_ERROR, "Couldn't init SDL joystick subsystem: %s", SDL_GetError() );
            return 0;
        }

    /* get thenumber of joysticks */
    numJoysticks = SDL_NumJoysticks();

    /* quit the joystick subsystem if necessary */
    if (!joyWasInit)
        SDL_QuitSubSystem(SDL_INIT_JOYSTICK);

    return numJoysticks;
}