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
typedef  int /*<<< orphan*/  wait_queue_head_t ;
struct fast_timer {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  D1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fast_timer_pending (struct fast_timer*) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printk (char*,unsigned long) ; 
 int /*<<< orphan*/  start_one_shot_timer (struct fast_timer*,int /*<<< orphan*/ ,unsigned long,unsigned long,char*) ; 
 int /*<<< orphan*/  wait_event (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_func ; 

void schedule_usleep(unsigned long us)
{
  struct fast_timer t;
  wait_queue_head_t sleep_wait;
  init_waitqueue_head(&sleep_wait);

  D1(printk("schedule_usleep(%d)\n", us));
  start_one_shot_timer(&t, wake_up_func, (unsigned long)&sleep_wait, us,
                       "usleep");
	/* Uninterruptible sleep on the fast timer. (The condition is somewhat
	 * redundant since the timer is what wakes us up.) */
	wait_event(sleep_wait, !fast_timer_pending(&t));

  D1(printk("done schedule_usleep(%d)\n", us));
}