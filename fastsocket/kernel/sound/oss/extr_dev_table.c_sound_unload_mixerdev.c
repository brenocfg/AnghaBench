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
 int /*<<< orphan*/ ** mixer_devs ; 
 int /*<<< orphan*/  num_mixers ; 
 int /*<<< orphan*/  unregister_sound_mixer (int) ; 

void sound_unload_mixerdev(int dev)
{
	if (dev != -1) {
		mixer_devs[dev] = NULL;
		unregister_sound_mixer(dev<<4);
		num_mixers--;
	}
}