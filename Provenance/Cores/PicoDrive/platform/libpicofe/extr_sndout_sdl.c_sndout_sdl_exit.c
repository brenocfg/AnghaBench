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
 int /*<<< orphan*/  SDL_INIT_AUDIO ; 
 int /*<<< orphan*/  SDL_QuitSubSystem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sndout_sdl_stop () ; 
 scalar_t__ started ; 

void sndout_sdl_exit(void)
{
	if (started)
		sndout_sdl_stop();
	SDL_QuitSubSystem(SDL_INIT_AUDIO);
}