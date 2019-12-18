#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct audio_operations {scalar_t__ open_mode; int go; int enable_bits; TYPE_1__* d; } ;
struct TYPE_2__ {int /*<<< orphan*/  (* trigger ) (int,int) ;} ;

/* Variables and functions */
 struct audio_operations** audio_devs ; 
 int num_audiodevs ; 
 int /*<<< orphan*/  stub1 (int,int) ; 

void DMAbuf_start_devices(unsigned int devmask)
{
	struct audio_operations *adev;
	int dev;

	for (dev = 0; dev < num_audiodevs; dev++) {
		if (!(devmask & (1 << dev)))
			continue;
		if (!(adev = audio_devs[dev]))
			continue;
		if (adev->open_mode == 0)
			continue;
		if (adev->go)
			continue;
		/* OK to start the device */
		adev->go = 1;
		if (adev->d->trigger)
			adev->d->trigger(dev,adev->enable_bits * adev->go);
	}
}