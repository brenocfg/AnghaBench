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
 int EINVAL ; 
 int HCI_LCD_BRIGHTNESS_LEVELS ; 
 int set_lcd (int) ; 
 int sscanf (char const*,char*,int*) ; 

__attribute__((used)) static unsigned long write_lcd(const char *buffer, unsigned long count)
{
	int value;
	int ret;

	if (sscanf(buffer, " brightness : %i", &value) == 1 &&
	    value >= 0 && value < HCI_LCD_BRIGHTNESS_LEVELS) {
		ret = set_lcd(value);
		if (ret == 0)
			ret = count;
	} else {
		ret = -EINVAL;
	}
	return ret;
}