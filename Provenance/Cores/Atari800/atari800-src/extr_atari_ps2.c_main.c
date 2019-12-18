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
 int /*<<< orphan*/  Atari800_Frame () ; 
 int /*<<< orphan*/  Atari800_Initialise (int*,char**) ; 
 scalar_t__ Atari800_display_screen ; 
 int /*<<< orphan*/  INPUT_key_code ; 
 int /*<<< orphan*/  PLATFORM_DisplayScreen () ; 
 int /*<<< orphan*/  PLATFORM_Keyboard () ; 
 int /*<<< orphan*/  loadModules () ; 

int main(int argc, char **argv)
{
	loadModules();
	/* initialise Atari800 core */
	if (!Atari800_Initialise(&argc, argv))
		return 3;

	/* main loop */
	for (;;) {
		INPUT_key_code = PLATFORM_Keyboard();
		Atari800_Frame();
		if (Atari800_display_screen){
			PLATFORM_DisplayScreen();}
	}
}