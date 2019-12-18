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
struct in_sdl_state {int /*<<< orphan*/ * joy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SDL_JoystickClose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct in_sdl_state*) ; 

__attribute__((used)) static void in_sdl_free(void *drv_data)
{
	struct in_sdl_state *state = drv_data;

	if (state != NULL) {
		if (state->joy != NULL)
			SDL_JoystickClose(state->joy);
		free(state);
	}
}