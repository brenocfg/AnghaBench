#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_7__ {void* (* entry ) (void*) ;void* arg; int /*<<< orphan*/  cur_state; } ;
typedef  TYPE_1__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  __libc_start_hook (int /*<<< orphan*/ ,TYPE_1__*) ; 
 scalar_t__ __lwp_statedormant (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_loadenv (TYPE_1__*) ; 
 int /*<<< orphan*/  __lwp_thread_ready (TYPE_1__*) ; 
 int /*<<< orphan*/  _thr_executing ; 
 int /*<<< orphan*/  kprintf (char*,TYPE_1__*,void* (*) (void*),void*,int /*<<< orphan*/ ) ; 

u32 __lwp_thread_start(lwp_cntrl *thethread,void* (*entry)(void*),void *arg)
{
#ifdef _LWPTHREADS_DEBUG
	kprintf("__lwp_thread_start(%p,%p,%p,%d)\n",thethread,entry,arg,thethread->cur_state);
#endif
	if(__lwp_statedormant(thethread->cur_state)) {
		thethread->entry = entry;
		thethread->arg = arg;
		__lwp_thread_loadenv(thethread);
		__lwp_thread_ready(thethread);
		__libc_start_hook(_thr_executing,thethread);
		return 1;
	}
	return 0;
}