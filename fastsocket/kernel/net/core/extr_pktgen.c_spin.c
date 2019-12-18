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
struct pktgen_dev {int /*<<< orphan*/  delay; void* next_tx; int /*<<< orphan*/  idle_acc; scalar_t__ running; } ;
struct hrtimer_sleeper {int /*<<< orphan*/  timer; int /*<<< orphan*/ * task; } ;
typedef  scalar_t__ s64 ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  hrtimer_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_expires_remaining (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hrtimer_init_on_stack (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_init_sleeper (struct hrtimer_sleeper*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_set_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hrtimer_start_expires (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* ktime_add_ns (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_now () ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_us (int /*<<< orphan*/ ) ; 
 scalar_t__ likely (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (scalar_t__) ; 

__attribute__((used)) static void spin(struct pktgen_dev *pkt_dev, ktime_t spin_until)
{
	ktime_t start_time, end_time;
	s64 remaining;
	struct hrtimer_sleeper t;

	hrtimer_init_on_stack(&t.timer, CLOCK_MONOTONIC, HRTIMER_MODE_ABS);
	hrtimer_set_expires(&t.timer, spin_until);

	remaining = ktime_to_us(hrtimer_expires_remaining(&t.timer));
	if (remaining <= 0) {
		pkt_dev->next_tx = ktime_add_ns(spin_until, pkt_dev->delay);
		return;
	}

	start_time = ktime_now();
	if (remaining < 100)
		udelay(remaining); 	/* really small just spin */
	else {
		/* see do_nanosleep */
		hrtimer_init_sleeper(&t, current);
		do {
			set_current_state(TASK_INTERRUPTIBLE);
			hrtimer_start_expires(&t.timer, HRTIMER_MODE_ABS);
			if (!hrtimer_active(&t.timer))
				t.task = NULL;

			if (likely(t.task))
				schedule();

			hrtimer_cancel(&t.timer);
		} while (t.task && pkt_dev->running && !signal_pending(current));
		__set_current_state(TASK_RUNNING);
	}
	end_time = ktime_now();

	pkt_dev->idle_acc += ktime_to_ns(ktime_sub(end_time, start_time));
	pkt_dev->next_tx = ktime_add_ns(end_time, pkt_dev->delay);
}