#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct device {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  state; } ;
struct backlight_device {int /*<<< orphan*/  ops_lock; TYPE_2__ props; TYPE_1__* ops; } ;
typedef  int /*<<< orphan*/  pm_message_t ;
struct TYPE_3__ {int options; } ;

/* Variables and functions */
 int /*<<< orphan*/  BL_CORE_SUSPENDED ; 
 int BL_CORE_SUSPENDRESUME ; 
 int /*<<< orphan*/  backlight_update_status (struct backlight_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct backlight_device* to_backlight_device (struct device*) ; 

__attribute__((used)) static int backlight_suspend(struct device *dev, pm_message_t state)
{
	struct backlight_device *bd = to_backlight_device(dev);

	if (bd->ops->options & BL_CORE_SUSPENDRESUME) {
		mutex_lock(&bd->ops_lock);
		bd->props.state |= BL_CORE_SUSPENDED;
		backlight_update_status(bd);
		mutex_unlock(&bd->ops_lock);
	}

	return 0;
}