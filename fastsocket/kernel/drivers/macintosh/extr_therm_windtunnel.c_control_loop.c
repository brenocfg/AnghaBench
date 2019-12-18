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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ kthread_should_stop () ; 
 int /*<<< orphan*/  msleep_interruptible (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  poll_temp () ; 
 int /*<<< orphan*/  restore_regs () ; 
 int /*<<< orphan*/  setup_hardware () ; 
 TYPE_1__ x ; 

__attribute__((used)) static int control_loop(void *dummy)
{
	mutex_lock(&x.lock);
	setup_hardware();
	mutex_unlock(&x.lock);

	for (;;) {
		msleep_interruptible(8000);
		if (kthread_should_stop())
			break;

		mutex_lock(&x.lock);
		poll_temp();
		mutex_unlock(&x.lock);
	}

	mutex_lock(&x.lock);
	restore_regs();
	mutex_unlock(&x.lock);

	return 0;
}