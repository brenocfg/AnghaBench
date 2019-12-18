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
struct gc {int /*<<< orphan*/  mutex; TYPE_1__* pd; int /*<<< orphan*/  timer; int /*<<< orphan*/  used; } ;
struct TYPE_2__ {int /*<<< orphan*/  port; } ;

/* Variables and functions */
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 struct gc* input_get_drvdata (struct input_dev*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  parport_release (TYPE_1__*) ; 
 int /*<<< orphan*/  parport_write_control (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void gc_close(struct input_dev *dev)
{
	struct gc *gc = input_get_drvdata(dev);

	mutex_lock(&gc->mutex);
	if (!--gc->used) {
		del_timer_sync(&gc->timer);
		parport_write_control(gc->pd->port, 0x00);
		parport_release(gc->pd);
	}
	mutex_unlock(&gc->mutex);
}