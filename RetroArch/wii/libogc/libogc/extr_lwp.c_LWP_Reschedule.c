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

/* Variables and functions */
 int /*<<< orphan*/  __lwp_rotate_readyqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

void LWP_Reschedule(u32 prio)
{
	__lwp_thread_dispatchdisable();
	__lwp_rotate_readyqueue(prio);
	__lwp_thread_dispatchenable();
}