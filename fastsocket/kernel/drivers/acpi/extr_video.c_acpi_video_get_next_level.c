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
typedef  int u32 ;
struct acpi_video_device {TYPE_1__* brightness; } ;
struct TYPE_2__ {int count; int* levels; } ;

/* Variables and functions */
#define  ACPI_VIDEO_NOTIFY_CYCLE_BRIGHTNESS 132 
#define  ACPI_VIDEO_NOTIFY_DEC_BRIGHTNESS 131 
#define  ACPI_VIDEO_NOTIFY_DISPLAY_OFF 130 
#define  ACPI_VIDEO_NOTIFY_INC_BRIGHTNESS 129 
#define  ACPI_VIDEO_NOTIFY_ZERO_BRIGHTNESS 128 
 scalar_t__ abs (int) ; 

__attribute__((used)) static int
acpi_video_get_next_level(struct acpi_video_device *device,
			  u32 level_current, u32 event)
{
	int min, max, min_above, max_below, i, l, delta = 255;
	max = max_below = 0;
	min = min_above = 255;
	/* Find closest level to level_current */
	for (i = 2; i < device->brightness->count; i++) {
		l = device->brightness->levels[i];
		if (abs(l - level_current) < abs(delta)) {
			delta = l - level_current;
			if (!delta)
				break;
		}
	}
	/* Ajust level_current to closest available level */
	level_current += delta;
	for (i = 2; i < device->brightness->count; i++) {
		l = device->brightness->levels[i];
		if (l < min)
			min = l;
		if (l > max)
			max = l;
		if (l < min_above && l > level_current)
			min_above = l;
		if (l > max_below && l < level_current)
			max_below = l;
	}

	switch (event) {
	case ACPI_VIDEO_NOTIFY_CYCLE_BRIGHTNESS:
		return (level_current < max) ? min_above : min;
	case ACPI_VIDEO_NOTIFY_INC_BRIGHTNESS:
		return (level_current < max) ? min_above : max;
	case ACPI_VIDEO_NOTIFY_DEC_BRIGHTNESS:
		return (level_current > min) ? max_below : min;
	case ACPI_VIDEO_NOTIFY_ZERO_BRIGHTNESS:
	case ACPI_VIDEO_NOTIFY_DISPLAY_OFF:
		return 0;
	default:
		return level_current;
	}
}