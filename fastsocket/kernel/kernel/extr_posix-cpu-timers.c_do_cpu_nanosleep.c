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
struct timespec {int tv_sec; int tv_nsec; } ;
struct TYPE_6__ {scalar_t__ sched; } ;
struct TYPE_4__ {TYPE_3__ expires; } ;
struct TYPE_5__ {TYPE_1__ cpu; } ;
struct k_itimer {int it_overrun; struct timespec it_value; int /*<<< orphan*/  it_lock; TYPE_2__ it; int /*<<< orphan*/  it_process; int /*<<< orphan*/  it_clock; } ;
struct itimerspec {int it_overrun; struct timespec it_value; int /*<<< orphan*/  it_lock; TYPE_2__ it; int /*<<< orphan*/  it_process; int /*<<< orphan*/  it_clock; } ;
typedef  int /*<<< orphan*/  clockid_t ;

/* Variables and functions */
 int ERESTART_RESTARTBLOCK ; 
 int /*<<< orphan*/  TASK_INTERRUPTIBLE ; 
 int /*<<< orphan*/  __set_current_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  memset (struct k_itimer*,int /*<<< orphan*/ ,int) ; 
 int posix_cpu_timer_create (struct k_itimer*) ; 
 int posix_cpu_timer_set (struct k_itimer*,int,struct k_itimer*,struct k_itimer*) ; 
 int /*<<< orphan*/  sample_to_timespec (int /*<<< orphan*/  const,TYPE_3__,struct timespec*) ; 
 int /*<<< orphan*/  schedule () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int do_cpu_nanosleep(const clockid_t which_clock, int flags,
			    struct timespec *rqtp, struct itimerspec *it)
{
	struct k_itimer timer;
	int error;

	/*
	 * Set up a temporary timer and then wait for it to go off.
	 */
	memset(&timer, 0, sizeof timer);
	spin_lock_init(&timer.it_lock);
	timer.it_clock = which_clock;
	timer.it_overrun = -1;
	error = posix_cpu_timer_create(&timer);
	timer.it_process = current;
	if (!error) {
		static struct itimerspec zero_it;

		memset(it, 0, sizeof *it);
		it->it_value = *rqtp;

		spin_lock_irq(&timer.it_lock);
		error = posix_cpu_timer_set(&timer, flags, it, NULL);
		if (error) {
			spin_unlock_irq(&timer.it_lock);
			return error;
		}

		while (!signal_pending(current)) {
			if (timer.it.cpu.expires.sched == 0) {
				/*
				 * Our timer fired and was reset.
				 */
				spin_unlock_irq(&timer.it_lock);
				return 0;
			}

			/*
			 * Block until cpu_timer_fire (or a signal) wakes us.
			 */
			__set_current_state(TASK_INTERRUPTIBLE);
			spin_unlock_irq(&timer.it_lock);
			schedule();
			spin_lock_irq(&timer.it_lock);
		}

		/*
		 * We were interrupted by a signal.
		 */
		sample_to_timespec(which_clock, timer.it.cpu.expires, rqtp);
		posix_cpu_timer_set(&timer, 0, &zero_it, it);
		spin_unlock_irq(&timer.it_lock);

		if ((it->it_value.tv_sec | it->it_value.tv_nsec) == 0) {
			/*
			 * It actually did fire already.
			 */
			return 0;
		}

		error = -ERESTART_RESTARTBLOCK;
	}

	return error;
}