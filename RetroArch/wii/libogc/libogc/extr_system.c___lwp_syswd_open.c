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
typedef  int /*<<< orphan*/  syswd_t ;
typedef  int /*<<< orphan*/  alarm_st ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_CHECK_SYSWD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_OBJMASKID (int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_objmgr_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sys_alarm_objects ; 

__attribute__((used)) static __inline__ alarm_st* __lwp_syswd_open(syswd_t wd)
{
	LWP_CHECK_SYSWD(wd);
	return (alarm_st*)__lwp_objmgr_get(&sys_alarm_objects,LWP_OBJMASKID(wd));
}