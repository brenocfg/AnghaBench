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
 int FALSE ; 
 int TRUE ; 
 unsigned int VIDEOMODE_HORIZONTAL_CUSTOM ; 
 unsigned int VIDEOMODE_MAX_HORIZONTAL_AREA ; 
 unsigned int VIDEOMODE_MIN_HORIZONTAL_AREA ; 
 int /*<<< orphan*/  VIDEOMODE_Update () ; 
 unsigned int VIDEOMODE_custom_horizontal_area ; 
 unsigned int VIDEOMODE_horizontal_area ; 

int VIDEOMODE_SetCustomHorizontalArea(unsigned int value)
{
	unsigned int old_value = VIDEOMODE_custom_horizontal_area;
	unsigned int old_area = VIDEOMODE_horizontal_area;
	if (value < VIDEOMODE_MIN_HORIZONTAL_AREA)
		return FALSE;
	if (value > VIDEOMODE_MAX_HORIZONTAL_AREA)
		value = VIDEOMODE_MAX_HORIZONTAL_AREA;
	if (value != VIDEOMODE_custom_horizontal_area || VIDEOMODE_horizontal_area != VIDEOMODE_HORIZONTAL_CUSTOM) {
		VIDEOMODE_custom_horizontal_area = value;
		VIDEOMODE_horizontal_area = VIDEOMODE_HORIZONTAL_CUSTOM;
		if (!VIDEOMODE_Update()) {
			VIDEOMODE_custom_horizontal_area = old_value;
			VIDEOMODE_horizontal_area = old_area;
			return FALSE;
		}
	}
	return TRUE;
}