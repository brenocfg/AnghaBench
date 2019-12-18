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
 scalar_t__* Joysticks ; 
 int MAX_JOYSTICKS ; 
 int /*<<< orphan*/  SDL_INIT_JOYSTICK ; 
 int /*<<< orphan*/  SDL_JoystickClose (scalar_t__) ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jinited ; 

int KillJoysticks (void)
{
	int n;			/* joystick index */

	if(!jinited) return(0);
	for (n = 0; n < MAX_JOYSTICKS; n++)
	{
		if (Joysticks[n] != 0)
 	  	 SDL_JoystickClose(Joysticks[n]);
		Joysticks[n]=0;
	}
	SDL_QuitSubSystem(SDL_INIT_JOYSTICK);
	return(1);
}