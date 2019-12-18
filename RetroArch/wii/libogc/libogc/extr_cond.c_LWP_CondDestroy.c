#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int s32 ;
typedef  int /*<<< orphan*/  cond_t ;
struct TYPE_4__ {int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ cond_st ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  __lwp_cond_free (TYPE_1__*) ; 
 TYPE_1__* __lwp_cond_open (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 scalar_t__ __lwp_threadqueue_first (int /*<<< orphan*/ *) ; 

s32 LWP_CondDestroy(cond_t cond)
{
	cond_st *ptr = __lwp_cond_open(cond);
	if(!ptr) return -1;

	if(__lwp_threadqueue_first(&ptr->wait_queue)) {
		__lwp_thread_dispatchenable();
		return EBUSY;
	}
	__lwp_thread_dispatchenable();

	__lwp_cond_free(ptr);
	return 0;
}