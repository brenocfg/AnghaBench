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
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  syswd_t ;

/* Variables and functions */
 size_t STACKSIZE ; 
 int /*<<< orphan*/  SYS_SwitchFiber (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 scalar_t__ l2cap_tmr ; 
 int /*<<< orphan*/ * ppc_stack ; 

__attribute__((used)) static void bt_alarmhandler(syswd_t alarm,void *cbarg)
{
	__lwp_thread_dispatchdisable();
	SYS_SwitchFiber(0,0,0,0,(u32)l2cap_tmr,(u32)(&ppc_stack[STACKSIZE]));
	__lwp_thread_dispatchunnest();
}