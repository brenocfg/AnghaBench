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
 int /*<<< orphan*/  psp_msleep (int) ; 
 int samples_block ; 
 int samples_done ; 
 int samples_made ; 
 int /*<<< orphan*/  sound_thread_exit ; 

void pemu_sound_wait(void)
{
	// TODO: test this
	while (!sound_thread_exit && samples_made - samples_done > samples_block * 4)
		psp_msleep(10);
}