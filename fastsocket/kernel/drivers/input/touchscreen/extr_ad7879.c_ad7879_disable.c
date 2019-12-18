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
struct ad7879 {int disabled; int /*<<< orphan*/  mutex; TYPE_1__* bus; int /*<<< orphan*/  timer; int /*<<< orphan*/  work; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  AD7879_PM (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AD7879_PM_SHUTDOWN ; 
 int /*<<< orphan*/  AD7879_REG_CTRL2 ; 
 int /*<<< orphan*/  ad7879_ts_event_release (struct ad7879*) ; 
 int /*<<< orphan*/  ad7879_write (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 scalar_t__ del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  disable_irq (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ad7879_disable(struct ad7879 *ts)
{
	mutex_lock(&ts->mutex);

	if (!ts->disabled) {

		ts->disabled = 1;
		disable_irq(ts->bus->irq);

		cancel_work_sync(&ts->work);

		if (del_timer_sync(&ts->timer))
			ad7879_ts_event_release(ts);

		ad7879_write(ts->bus, AD7879_REG_CTRL2,
			     AD7879_PM(AD7879_PM_SHUTDOWN));
	}

	mutex_unlock(&ts->mutex);
}