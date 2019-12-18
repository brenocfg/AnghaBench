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
struct slow_work {int /*<<< orphan*/  flags; int /*<<< orphan*/  ops; } ;
struct TYPE_2__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct delayed_slow_work {TYPE_1__ timer; struct slow_work work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int ECANCELED ; 
 int /*<<< orphan*/  SLOW_WORK_CANCELLING ; 
 int /*<<< orphan*/  SLOW_WORK_DELAYED ; 
 int /*<<< orphan*/  SLOW_WORK_PENDING ; 
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  delayed_slow_work_timer ; 
 scalar_t__ jiffies ; 
 int slow_work_enqueue (struct slow_work*) ; 
 int slow_work_get_ref (struct slow_work*) ; 
 int /*<<< orphan*/  slow_work_queue_lock ; 
 scalar_t__ slow_work_user_count ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_and_set_bit_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int delayed_slow_work_enqueue(struct delayed_slow_work *dwork,
			      unsigned long delay)
{
	struct slow_work *work = &dwork->work;
	unsigned long flags;
	int ret;

	if (delay == 0)
		return slow_work_enqueue(&dwork->work);

	BUG_ON(slow_work_user_count <= 0);
	BUG_ON(!work);
	BUG_ON(!work->ops);

	if (test_bit(SLOW_WORK_CANCELLING, &work->flags))
		return -ECANCELED;

	if (!test_and_set_bit_lock(SLOW_WORK_PENDING, &work->flags)) {
		spin_lock_irqsave(&slow_work_queue_lock, flags);

		if (test_bit(SLOW_WORK_CANCELLING, &work->flags))
			goto cancelled;

		/* the timer holds a reference whilst it is pending */
		ret = slow_work_get_ref(work);
		if (ret < 0)
			goto cant_get_ref;

		if (test_and_set_bit(SLOW_WORK_DELAYED, &work->flags))
			BUG();
		dwork->timer.expires = jiffies + delay;
		dwork->timer.data = (unsigned long) work;
		dwork->timer.function = delayed_slow_work_timer;
		add_timer(&dwork->timer);

		spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	}

	return 0;

cancelled:
	ret = -ECANCELED;
cant_get_ref:
	spin_unlock_irqrestore(&slow_work_queue_lock, flags);
	return ret;
}