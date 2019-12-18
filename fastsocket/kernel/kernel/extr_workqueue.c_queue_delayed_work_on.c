#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct workqueue_struct {int dummy; } ;
struct work_struct {int /*<<< orphan*/  entry; } ;
struct timer_list {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct delayed_work {struct timer_list timer; struct work_struct work; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  WORK_STRUCT_PENDING ; 
 int /*<<< orphan*/  add_timer (struct timer_list*) ; 
 int /*<<< orphan*/  add_timer_on (struct timer_list*,int) ; 
 int /*<<< orphan*/  delayed_work_timer_fn ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  raw_smp_processor_id () ; 
 int /*<<< orphan*/  set_wq_data (struct work_struct*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_and_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int timer_pending (struct timer_list*) ; 
 int /*<<< orphan*/  timer_stats_timer_set_start_info (struct timer_list*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  work_data_bits (struct work_struct*) ; 
 int /*<<< orphan*/  wq_per_cpu (struct workqueue_struct*,int /*<<< orphan*/ ) ; 

int queue_delayed_work_on(int cpu, struct workqueue_struct *wq,
			struct delayed_work *dwork, unsigned long delay)
{
	int ret = 0;
	struct timer_list *timer = &dwork->timer;
	struct work_struct *work = &dwork->work;

	if (!test_and_set_bit(WORK_STRUCT_PENDING, work_data_bits(work))) {
		BUG_ON(timer_pending(timer));
		BUG_ON(!list_empty(&work->entry));

		timer_stats_timer_set_start_info(&dwork->timer);

		/* This stores cwq for the moment, for the timer_fn */
		set_wq_data(work, wq_per_cpu(wq, raw_smp_processor_id()));
		timer->expires = jiffies + delay;
		timer->data = (unsigned long)dwork;
		timer->function = delayed_work_timer_fn;

		if (unlikely(cpu >= 0))
			add_timer_on(timer, cpu);
		else
			add_timer(timer);
		ret = 1;
	}
	return ret;
}