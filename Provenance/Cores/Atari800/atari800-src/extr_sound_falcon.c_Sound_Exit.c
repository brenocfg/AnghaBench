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
 int /*<<< orphan*/  MFP_IRQ_off ; 
 int /*<<< orphan*/  Mfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Supexec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dsp_buffer1 ; 
 scalar_t__ sound_enabled ; 

void Sound_Exit(void)
{
	if (sound_enabled) {
		Supexec(MFP_IRQ_off);
		Mfree(dsp_buffer1);
	}
}