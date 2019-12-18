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
struct TYPE_5__ {void* start_per; int /*<<< orphan*/  alarm; TYPE_1__ object; scalar_t__ ticks; void* cb_arg; int /*<<< orphan*/  alarmhandler; void* periodic; } ;
typedef  TYPE_2__ alarm_st ;

/* Variables and functions */
 TYPE_2__* __lwp_syswd_open (scalar_t__) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 void* __lwp_wd_calc_ticks (struct timespec const*) ; 
 int /*<<< orphan*/  __lwp_wd_initialize (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  __lwp_wd_insert_ticks (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  __sys_alarmhandler ; 

s32 SYS_SetPeriodicAlarm(syswd_t thealarm,const struct timespec *tp_start,const struct timespec *tp_period,alarmcallback cb,void *cbarg)
{
	alarm_st *alarm;

	alarm = __lwp_syswd_open(thealarm);
	if(!alarm) return -1;

	alarm->start_per = __lwp_wd_calc_ticks(tp_start);
	alarm->periodic = __lwp_wd_calc_ticks(tp_period);
	alarm->alarmhandler = cb;
	alarm->cb_arg = cbarg;

	alarm->ticks = 0;

	__lwp_wd_initialize(&alarm->alarm,__sys_alarmhandler,alarm->object.id,(void*)thealarm);
	__lwp_wd_insert_ticks(&alarm->alarm,alarm->start_per);
	__lwp_thread_dispatchenable();
	return 0;
}