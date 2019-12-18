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
struct TYPE_2__ {int /*<<< orphan*/  state; } ;
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_1__ props; } ;

/* Variables and functions */
 int /*<<< orphan*/  GENERICBL_BATTLOW ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 struct backlight_device* generic_backlight_device ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void corgibl_limit_intensity(int limit)
{
	struct backlight_device *bd = generic_backlight_device;

	mutex_lock(&bd->ops_lock);
	if (limit)
		bd->props.state |= GENERICBL_BATTLOW;
	else
		bd->props.state &= ~GENERICBL_BATTLOW;
	backlight_update_status(generic_backlight_device);
	mutex_unlock(&bd->ops_lock);
}