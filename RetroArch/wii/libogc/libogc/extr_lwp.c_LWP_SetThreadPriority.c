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
typedef  scalar_t__ lwp_t ;
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 scalar_t__ LWP_GetSelf () ; 
 scalar_t__ LWP_THREAD_NULL ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/ * __lwp_cntrl_open (scalar_t__) ; 
 int /*<<< orphan*/  __lwp_priotocore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_changepriority (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 

void LWP_SetThreadPriority(lwp_t thethread,u32 prio)
{
	lwp_cntrl *lwp_thread;

	if(thethread==LWP_THREAD_NULL) thethread = LWP_GetSelf();

	lwp_thread = __lwp_cntrl_open(thethread);
	if(!lwp_thread) return;

	__lwp_thread_changepriority(lwp_thread,__lwp_priotocore(prio),TRUE);
	__lwp_thread_dispatchenable();
}