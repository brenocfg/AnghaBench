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
 int SDL_InitSubSystem (int /*<<< orphan*/ ) ; 

int sndout_sdl_init(void)
{
	int ret;

	ret = SDL_InitSubSystem(SDL_INIT_AUDIO);
	if (ret != 0)
		return -1;

	return 0;
}