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
 int MAX_SYNTH_DEV ; 
 int num_synths ; 
 int /*<<< orphan*/ ** synth_devs ; 

int sound_alloc_synthdev(void)
{
	int i;

	for (i = 0; i < MAX_SYNTH_DEV; i++) {
		if (synth_devs[i] == NULL) {
			if (i >= num_synths)
				num_synths++;
			return i;
		}
	}
	return -1;
}