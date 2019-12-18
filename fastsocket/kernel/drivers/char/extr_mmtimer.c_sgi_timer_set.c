#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct timespec {int dummy; } ;
struct rb_node {int dummy; } ;
struct mmtimer {int /*<<< orphan*/  cpu; struct k_itimer* timer; } ;
struct TYPE_4__ {size_t node; unsigned long incr; unsigned long expires; int /*<<< orphan*/  clock; } ;
struct TYPE_5__ {TYPE_1__ mmtimer; } ;
struct k_itimer {TYPE_2__ it; } ;
struct itimerspec {struct timespec it_interval; struct timespec it_value; } ;
typedef  size_t cnodeid_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; struct rb_node* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  COMPARATOR ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int TIMER_ABSTIME ; 
 int /*<<< orphan*/  TIMER_SET ; 
 int /*<<< orphan*/  cnodeid_to_nasid (size_t) ; 
 size_t cpu_to_node (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  getnstimeofday (struct timespec*) ; 
 struct mmtimer* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmtimer_add_list (struct mmtimer*) ; 
 int /*<<< orphan*/  mmtimer_disable_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mmtimer_set_next_timer (size_t) ; 
 int /*<<< orphan*/  preempt_disable () ; 
 int /*<<< orphan*/  preempt_enable () ; 
 unsigned long rtc_time () ; 
 unsigned long sgi_clock_period ; 
 int /*<<< orphan*/  sgi_timer_del (struct k_itimer*) ; 
 int /*<<< orphan*/  sgi_timer_get (struct k_itimer*,struct itimerspec*) ; 
 int /*<<< orphan*/  smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 TYPE_3__* timers ; 
 unsigned long timespec_to_ns (struct timespec*) ; 

__attribute__((used)) static int sgi_timer_set(struct k_itimer *timr, int flags,
	struct itimerspec * new_setting,
	struct itimerspec * old_setting)
{
	unsigned long when, period, irqflags;
	int err = 0;
	cnodeid_t nodeid;
	struct mmtimer *base;
	struct rb_node *n;

	if (old_setting)
		sgi_timer_get(timr, old_setting);

	sgi_timer_del(timr);
	when = timespec_to_ns(&new_setting->it_value);
	period = timespec_to_ns(&new_setting->it_interval);

	if (when == 0)
		/* Clear timer */
		return 0;

	base = kmalloc(sizeof(struct mmtimer), GFP_KERNEL);
	if (base == NULL)
		return -ENOMEM;

	if (flags & TIMER_ABSTIME) {
		struct timespec n;
		unsigned long now;

		getnstimeofday(&n);
		now = timespec_to_ns(&n);
		if (when > now)
			when -= now;
		else
			/* Fire the timer immediately */
			when = 0;
	}

	/*
	 * Convert to sgi clock period. Need to keep rtc_time() as near as possible
	 * to getnstimeofday() in order to be as faithful as possible to the time
	 * specified.
	 */
	when = (when + sgi_clock_period - 1) / sgi_clock_period + rtc_time();
	period = (period + sgi_clock_period - 1)  / sgi_clock_period;

	/*
	 * We are allocating a local SHub comparator. If we would be moved to another
	 * cpu then another SHub may be local to us. Prohibit that by switching off
	 * preemption.
	 */
	preempt_disable();

	nodeid =  cpu_to_node(smp_processor_id());

	/* Lock the node timer structure */
	spin_lock_irqsave(&timers[nodeid].lock, irqflags);

	base->timer = timr;
	base->cpu = smp_processor_id();

	timr->it.mmtimer.clock = TIMER_SET;
	timr->it.mmtimer.node = nodeid;
	timr->it.mmtimer.incr = period;
	timr->it.mmtimer.expires = when;

	n = timers[nodeid].next;

	/* Add the new struct mmtimer to node's timer list */
	mmtimer_add_list(base);

	if (timers[nodeid].next == n) {
		/* No need to reprogram comparator for now */
		spin_unlock_irqrestore(&timers[nodeid].lock, irqflags);
		preempt_enable();
		return err;
	}

	/* We need to reprogram the comparator */
	if (n)
		mmtimer_disable_int(cnodeid_to_nasid(nodeid), COMPARATOR);

	mmtimer_set_next_timer(nodeid);

	/* Unlock the node timer structure */
	spin_unlock_irqrestore(&timers[nodeid].lock, irqflags);

	preempt_enable();

	return err;
}