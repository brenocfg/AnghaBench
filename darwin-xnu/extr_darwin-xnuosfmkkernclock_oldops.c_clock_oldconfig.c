#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  timer_call_func_t ;
typedef  int /*<<< orphan*/  thread_call_func_t ;
typedef  TYPE_2__* clock_t ;
struct TYPE_5__ {TYPE_1__* cl_ops; } ;
struct TYPE_4__ {scalar_t__ (* c_config ) () ;} ;

/* Variables and functions */
 scalar_t__ alarm_done ; 
 int /*<<< orphan*/  alarm_done_call ; 
 scalar_t__ alarm_expire ; 
 int /*<<< orphan*/  alarm_expire_timer ; 
 int /*<<< orphan*/  alarm_lock ; 
 scalar_t__ alrm_seqno ; 
 int clock_count ; 
 TYPE_2__* clock_list ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 () ; 
 int /*<<< orphan*/  thread_call_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  timer_call_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
clock_oldconfig(void)
{
	clock_t			clock;
	int	i;

	simple_lock_init(&alarm_lock, 0);
	thread_call_setup(&alarm_done_call, (thread_call_func_t)alarm_done, NULL);
	timer_call_setup(&alarm_expire_timer, (timer_call_func_t)alarm_expire, NULL);

	/*
	 * Configure clock devices.
	 */
	for (i = 0; i < clock_count; i++) {
		clock = &clock_list[i];
		if (clock->cl_ops && clock->cl_ops->c_config) {
			if ((*clock->cl_ops->c_config)() == 0)
				clock->cl_ops = NULL;
		}
	}

	/* start alarm sequence numbers at 0 */
	alrm_seqno = 0;
}