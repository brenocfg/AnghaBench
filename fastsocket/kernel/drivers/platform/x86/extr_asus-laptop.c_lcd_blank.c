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
struct TYPE_2__ {int power; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 struct backlight_device* asus_backlight_device ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 

__attribute__((used)) static void lcd_blank(int blank)
{
	struct backlight_device *bd = asus_backlight_device;

	if (bd) {
		bd->props.power = blank;
		backlight_update_status(bd);
	}
}