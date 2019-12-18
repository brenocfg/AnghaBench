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
typedef  int /*<<< orphan*/  lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __lwp_thread_dispatchdisable () ; 
 int /*<<< orphan*/  __lwp_thread_dispatchunnest () ; 
 int /*<<< orphan*/  __lwp_thread_unblock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kprintf (char*,int /*<<< orphan*/ *) ; 

void __lwp_thread_delayended(void *arg)
{
	lwp_cntrl *thethread = (lwp_cntrl*)arg;
#ifdef _LWPTHREADS_DEBUG
	kprintf("__lwp_thread_delayended(%p)\n",thethread);
#endif
	if(!thethread) return;

	__lwp_thread_dispatchdisable();
	__lwp_thread_unblock(thethread);
	__lwp_thread_dispatchunnest();
}