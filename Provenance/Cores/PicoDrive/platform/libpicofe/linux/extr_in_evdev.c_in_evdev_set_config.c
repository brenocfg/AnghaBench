#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int abs_lzone; int abs_max_x; int abs_min_x; } ;
typedef  TYPE_1__ in_evdev_t ;

/* Variables and functions */
#define  IN_CFG_ABS_DEAD_ZONE 129 
#define  IN_CFG_BLOCKING 128 
 int in_evdev_set_blocking (TYPE_1__*,int) ; 

__attribute__((used)) static int in_evdev_set_config(void *drv_data, int what, int val)
{
	in_evdev_t *dev = drv_data;
	int tmp;

	switch (what) {
	case IN_CFG_BLOCKING:
		return in_evdev_set_blocking(dev, val);
	case IN_CFG_ABS_DEAD_ZONE:
		if (val < 1 || val > 99 || dev->abs_lzone == 0)
			return -1;
		/* XXX: based on X axis only, for now.. */
		tmp = (dev->abs_max_x - dev->abs_min_x) / 2;
		dev->abs_lzone = tmp - tmp * val / 100;
		if (dev->abs_lzone < 1)
			dev->abs_lzone = 1;
		else if (dev->abs_lzone >= tmp)
			dev->abs_lzone = tmp - 1;
		break;
	default:
		return -1;
	}

	return 0;
}