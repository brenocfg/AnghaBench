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
struct ucb1400_ts {int /*<<< orphan*/ * ts_task; int /*<<< orphan*/  ts_idev; scalar_t__ ts_restart; scalar_t__ irq_pending; int /*<<< orphan*/  ts_wait; int /*<<< orphan*/  ac97; } ;
struct task_struct {int dummy; } ;
struct sched_param {int sched_priority; } ;

/* Variables and functions */
 long MAX_SCHEDULE_TIMEOUT ; 
 int /*<<< orphan*/  SCHED_FIFO ; 
 struct task_struct* current ; 
 scalar_t__ kthread_should_stop () ; 
 long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  sched_setscheduler (struct task_struct*,int /*<<< orphan*/ ,struct sched_param*) ; 
 int /*<<< orphan*/  set_freezable () ; 
 int /*<<< orphan*/  ucb1400_adc_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_adc_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_handle_pending_irq (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  ucb1400_ts_event_release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_ts_evt_add (int /*<<< orphan*/ ,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  ucb1400_ts_irq_enable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ucb1400_ts_mode_int (int /*<<< orphan*/ ) ; 
 scalar_t__ ucb1400_ts_pen_up (int /*<<< orphan*/ ) ; 
 unsigned int ucb1400_ts_read_pressure (struct ucb1400_ts*) ; 
 unsigned int ucb1400_ts_read_xpos (struct ucb1400_ts*) ; 
 unsigned int ucb1400_ts_read_ypos (struct ucb1400_ts*) ; 
 int /*<<< orphan*/  wait_event_freezable_timeout (int /*<<< orphan*/ ,int,long) ; 

__attribute__((used)) static int ucb1400_ts_thread(void *_ucb)
{
	struct ucb1400_ts *ucb = _ucb;
	struct task_struct *tsk = current;
	int valid = 0;
	struct sched_param param = { .sched_priority = 1 };

	sched_setscheduler(tsk, SCHED_FIFO, &param);

	set_freezable();
	while (!kthread_should_stop()) {
		unsigned int x, y, p;
		long timeout;

		ucb->ts_restart = 0;

		if (ucb->irq_pending) {
			ucb->irq_pending = 0;
			ucb1400_handle_pending_irq(ucb);
		}

		ucb1400_adc_enable(ucb->ac97);
		x = ucb1400_ts_read_xpos(ucb);
		y = ucb1400_ts_read_ypos(ucb);
		p = ucb1400_ts_read_pressure(ucb);
		ucb1400_adc_disable(ucb->ac97);

		/* Switch back to interrupt mode. */
		ucb1400_ts_mode_int(ucb->ac97);

		msleep(10);

		if (ucb1400_ts_pen_up(ucb->ac97)) {
			ucb1400_ts_irq_enable(ucb->ac97);

			/*
			 * If we spat out a valid sample set last time,
			 * spit out a "pen off" sample here.
			 */
			if (valid) {
				ucb1400_ts_event_release(ucb->ts_idev);
				valid = 0;
			}

			timeout = MAX_SCHEDULE_TIMEOUT;
		} else {
			valid = 1;
			ucb1400_ts_evt_add(ucb->ts_idev, p, x, y);
			timeout = msecs_to_jiffies(10);
		}

		wait_event_freezable_timeout(ucb->ts_wait,
			ucb->irq_pending || ucb->ts_restart ||
			kthread_should_stop(), timeout);
	}

	/* Send the "pen off" if we are stopping with the pen still active */
	if (valid)
		ucb1400_ts_event_release(ucb->ts_idev);

	ucb->ts_task = NULL;
	return 0;
}