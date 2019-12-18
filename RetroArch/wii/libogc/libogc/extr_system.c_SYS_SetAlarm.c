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
typedef  scalar_t__ syswd_t ;
struct timespec {int dummy; } ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  alarmcallback ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  ticks; int /*<<< orphan*/  alarm; TYPE_1__ object; scalar_t__ start_per; scalar_t__ periodic; int /*<<< orphan*/  alarmhandler; void* cb_arg; } ;
typedef  TYPE_2__ alarm_st ;

/* Variables and functions */
 TYPE_2__* __lwp_syswd_open (scalar_t__) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwp_wd_calc_ticks (struct timespec const*) ; 
 int /*<<< orphan*/  __lwp_wd_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __sys_alarmhandler ; 

s32 SYS_SetAlarm(syswd_t thealarm,const struct timespec *tp,alarmcallback cb,void *cbarg)
{
	alarm_st *alarm;

	alarm = __lwp_syswd_open(thealarm);
	if(!alarm) return -1;

	alarm->cb_arg = cbarg;
	alarm->alarmhandler = cb;
	alarm->ticks = __lwp_wd_calc_ticks(tp);

	alarm->periodic = 0;
	alarm->start_per = 0;

	__lwp_wd_initialize(&alarm->alarm,__sys_alarmhandler,alarm->object.id,(void*)thealarm);
	__lwp_wd_insert_ticks(&alarm->alarm,alarm->ticks);
	__lwp_thread_dispatchenable();
	return 0;
}