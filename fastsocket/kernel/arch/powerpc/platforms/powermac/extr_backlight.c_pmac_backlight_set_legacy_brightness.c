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
 int __pmac_backlight_set_legacy_brightness (int) ; 

int pmac_backlight_set_legacy_brightness(int brightness)
{
	return __pmac_backlight_set_legacy_brightness(brightness);
}