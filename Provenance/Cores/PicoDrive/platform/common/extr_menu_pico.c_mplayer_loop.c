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
 int PBTN_MA3 ; 
 int /*<<< orphan*/  PDebugZ80Frame () ; 
 int /*<<< orphan*/  emu_sound_stop () ; 
 int /*<<< orphan*/  emu_sound_wait () ; 
 int in_menu_wait_any (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pemu_sound_start () ; 

__attribute__((used)) static void mplayer_loop(void)
{
	pemu_sound_start();

	while (1)
	{
		PDebugZ80Frame();
		if (in_menu_wait_any(NULL, 0) & PBTN_MA3)
			break;
		emu_sound_wait();
	}

	emu_sound_stop();
}