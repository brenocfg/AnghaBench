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
struct TYPE_2__ {int x; int abs_event; int /*<<< orphan*/  y; } ;
struct mousedev {TYPE_1__ packet; } ;
struct input_dev {int* absmax; int* absmin; } ;

/* Variables and functions */
#define  ABS_X 129 
#define  ABS_Y 128 
 int xres ; 
 int yres ; 

__attribute__((used)) static void mousedev_abs_event(struct input_dev *dev, struct mousedev *mousedev,
				unsigned int code, int value)
{
	int size;

	switch (code) {

	case ABS_X:
		size = dev->absmax[ABS_X] - dev->absmin[ABS_X];
		if (size == 0)
			size = xres ? : 1;
		if (value > dev->absmax[ABS_X])
			value = dev->absmax[ABS_X];
		if (value < dev->absmin[ABS_X])
			value = dev->absmin[ABS_X];
		mousedev->packet.x =
			((value - dev->absmin[ABS_X]) * xres) / size;
		mousedev->packet.abs_event = 1;
		break;

	case ABS_Y:
		size = dev->absmax[ABS_Y] - dev->absmin[ABS_Y];
		if (size == 0)
			size = yres ? : 1;
		if (value > dev->absmax[ABS_Y])
			value = dev->absmax[ABS_Y];
		if (value < dev->absmin[ABS_Y])
			value = dev->absmin[ABS_Y];
		mousedev->packet.y = yres -
			((value - dev->absmin[ABS_Y]) * yres) / size;
		mousedev->packet.abs_event = 1;
		break;
	}
}