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
struct TYPE_2__ {int brightness; } ;
struct backlight_device {TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  BACKLIGHT_UPDATE_HOTKEY ; 
 int /*<<< orphan*/  backlight_force_update (struct backlight_device*,int /*<<< orphan*/ ) ; 
 struct backlight_device* eeepc_backlight_device ; 

__attribute__((used)) static int notify_brn(void)
{
	/* returns the *previous* brightness, or -1 */
	struct backlight_device *bd = eeepc_backlight_device;
	if (bd) {
		int old = bd->props.brightness;
		backlight_force_update(bd, BACKLIGHT_UPDATE_HOTKEY);
		return old;
	}
	return -1;
}