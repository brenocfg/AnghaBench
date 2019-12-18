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
 int /*<<< orphan*/  DMAbuf_deinit (int) ; 
 int /*<<< orphan*/ ** audio_devs ; 
 int /*<<< orphan*/  unregister_sound_dsp (int) ; 

void sound_unload_audiodev(int dev)
{
	if (dev != -1) {
		DMAbuf_deinit(dev);
		audio_devs[dev] = NULL;
		unregister_sound_dsp((dev<<4)+3);
	}
}