#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  object; } ;
typedef  TYPE_1__ alarm_st ;

/* Variables and functions */
 scalar_t__ __lwp_objmgr_allocate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_objmgr_open (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  sys_alarm_objects ; 

__attribute__((used)) static alarm_st* __lwp_syswd_allocate()
{
	alarm_st *alarm;

	__lwp_thread_dispatchdisable();
	alarm = (alarm_st*)__lwp_objmgr_allocate(&sys_alarm_objects);
	if(alarm) {
		__lwp_objmgr_open(&sys_alarm_objects,&alarm->object);
		return alarm;
	}
	__lwp_thread_dispatchenable();
	return NULL;
}