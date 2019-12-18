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
struct TYPE_2__ {int brightness; scalar_t__ power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 scalar_t__ FB_BLANK_UNBLANK ; 
 int set_brightness (struct backlight_device*,int) ; 
 int set_lcd_state (int) ; 

__attribute__((used)) static int update_bl_status(struct backlight_device *bd)
{
	int rv;
	int value = bd->props.brightness;

	rv = set_brightness(bd, value);
	if (rv)
		return rv;

	value = (bd->props.power == FB_BLANK_UNBLANK) ? 1 : 0;
	return set_lcd_state(value);
}