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
struct input_dev {int dummy; } ;
struct gc {int /*<<< orphan*/  mutex; int /*<<< orphan*/  timer; TYPE_1__* pd; int /*<<< orphan*/  used; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 scalar_t__ GC_REFRESH_TIME ; 
 struct gc* input_get_drvdata (struct input_dev*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 int mutex_lock_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_claim (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int gc_open(struct input_dev *dev)
{
	struct gc *gc = input_get_drvdata(dev);
	int err;

	err = mutex_lock_interruptible(&gc->mutex);
	if (err)
		return err;

	if (!gc->used++) {
		parport_claim(gc->pd);
		parport_write_control(gc->pd->port, 0x04);
		mod_timer(&gc->timer, jiffies + GC_REFRESH_TIME);
	}

	mutex_unlock(&gc->mutex);
	return 0;
}