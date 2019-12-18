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
typedef  int syswd_t ;
typedef  int s32 ;
struct TYPE_4__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {TYPE_1__ object; scalar_t__ periodic; scalar_t__ start_per; scalar_t__ ticks; int /*<<< orphan*/ * alarmhandler; } ;
typedef  TYPE_2__ alarm_st ;

/* Variables and functions */
 int LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 int LWP_OBJMASKTYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJTYPE_SYSWD ; 
 TYPE_2__* __lwp_syswd_allocate () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

s32 SYS_CreateAlarm(syswd_t *thealarm)
{
	alarm_st *alarm;

	alarm = __lwp_syswd_allocate();
	if(!alarm) return -1;

	alarm->alarmhandler = NULL;
	alarm->ticks = 0;
	alarm->start_per = 0;
	alarm->periodic = 0;

	*thealarm = (LWP_OBJMASKTYPE(LWP_OBJTYPE_SYSWD)|LWP_OBJMASKID(alarm->object.id));
	__lwp_thread_dispatchenable();
	return 0;
}