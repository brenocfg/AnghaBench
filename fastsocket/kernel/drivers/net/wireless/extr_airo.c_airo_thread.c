#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  wait_queue_t ;
struct net_device {struct airo_info* ml_priv; } ;
struct TYPE_5__ {scalar_t__ event; } ;
struct airo_info {int /*<<< orphan*/  sem; scalar_t__ jobs; scalar_t__ flags; TYPE_1__ power; int /*<<< orphan*/  thr_wait; scalar_t__ scan_timeout; scalar_t__ expires; } ;
struct TYPE_6__ {int /*<<< orphan*/  state; } ;

/* Variables and functions */
 int /*<<< orphan*/  FLAG_FLASHING ; 
 int /*<<< orphan*/  JOB_AUTOWEP ; 
 int /*<<< orphan*/  JOB_DIE ; 
 int /*<<< orphan*/  JOB_EVENT ; 
 int /*<<< orphan*/  JOB_MIC ; 
 int /*<<< orphan*/  JOB_PROMISC ; 
 int /*<<< orphan*/  JOB_SCAN_RESULTS ; 
 int /*<<< orphan*/  JOB_STATS ; 
 int /*<<< orphan*/  JOB_WSTATS ; 
 int /*<<< orphan*/  JOB_XMIT ; 
 int /*<<< orphan*/  JOB_XMIT11 ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  TASK_RUNNING ; 
 int /*<<< orphan*/  add_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  airo_end_xmit (struct net_device*) ; 
 int /*<<< orphan*/  airo_end_xmit11 (struct net_device*) ; 
 int /*<<< orphan*/  airo_process_scan_results (struct airo_info*) ; 
 int /*<<< orphan*/  airo_read_stats (struct net_device*) ; 
 int /*<<< orphan*/  airo_read_wireless_stats (struct airo_info*) ; 
 int /*<<< orphan*/  airo_send_event (struct net_device*) ; 
 int /*<<< orphan*/  airo_set_promisc (struct airo_info*) ; 
 TYPE_2__* current ; 
 int down_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  freezing (TYPE_2__*) ; 
 int /*<<< orphan*/  init_waitqueue_entry (int /*<<< orphan*/ *,TYPE_2__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kthread_should_stop () ; 
 unsigned long max (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  micinit (struct airo_info*) ; 
 unsigned long min (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  remove_wait_queue (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  schedule_timeout (scalar_t__) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_freezable () ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ time_after_eq (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timer_func (struct net_device*) ; 
 int /*<<< orphan*/  try_to_freeze () ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int airo_thread(void *data) {
	struct net_device *dev = data;
	struct airo_info *ai = dev->ml_priv;
	int locked;

	set_freezable();
	while(1) {
		/* make swsusp happy with our thread */
		try_to_freeze();

		if (test_bit(JOB_DIE, &ai->jobs))
			break;

		if (ai->jobs) {
			locked = down_interruptible(&ai->sem);
		} else {
			wait_queue_t wait;

			init_waitqueue_entry(&wait, current);
			add_wait_queue(&ai->thr_wait, &wait);
			for (;;) {
				set_current_state(TASK_INTERRUPTIBLE);
				if (ai->jobs)
					break;
				if (ai->expires || ai->scan_timeout) {
					if (ai->scan_timeout &&
							time_after_eq(jiffies,ai->scan_timeout)){
						set_bit(JOB_SCAN_RESULTS, &ai->jobs);
						break;
					} else if (ai->expires &&
							time_after_eq(jiffies,ai->expires)){
						set_bit(JOB_AUTOWEP, &ai->jobs);
						break;
					}
					if (!kthread_should_stop() &&
					    !freezing(current)) {
						unsigned long wake_at;
						if (!ai->expires || !ai->scan_timeout) {
							wake_at = max(ai->expires,
								ai->scan_timeout);
						} else {
							wake_at = min(ai->expires,
								ai->scan_timeout);
						}
						schedule_timeout(wake_at - jiffies);
						continue;
					}
				} else if (!kthread_should_stop() &&
					   !freezing(current)) {
					schedule();
					continue;
				}
				break;
			}
			current->state = TASK_RUNNING;
			remove_wait_queue(&ai->thr_wait, &wait);
			locked = 1;
		}

		if (locked)
			continue;

		if (test_bit(JOB_DIE, &ai->jobs)) {
			up(&ai->sem);
			break;
		}

		if (ai->power.event || test_bit(FLAG_FLASHING, &ai->flags)) {
			up(&ai->sem);
			continue;
		}

		if (test_bit(JOB_XMIT, &ai->jobs))
			airo_end_xmit(dev);
		else if (test_bit(JOB_XMIT11, &ai->jobs))
			airo_end_xmit11(dev);
		else if (test_bit(JOB_STATS, &ai->jobs))
			airo_read_stats(dev);
		else if (test_bit(JOB_WSTATS, &ai->jobs))
			airo_read_wireless_stats(ai);
		else if (test_bit(JOB_PROMISC, &ai->jobs))
			airo_set_promisc(ai);
		else if (test_bit(JOB_MIC, &ai->jobs))
			micinit(ai);
		else if (test_bit(JOB_EVENT, &ai->jobs))
			airo_send_event(dev);
		else if (test_bit(JOB_AUTOWEP, &ai->jobs))
			timer_func(dev);
		else if (test_bit(JOB_SCAN_RESULTS, &ai->jobs))
			airo_process_scan_results(ai);
		else  /* Shouldn't get here, but we make sure to unlock */
			up(&ai->sem);
	}

	return 0;
}