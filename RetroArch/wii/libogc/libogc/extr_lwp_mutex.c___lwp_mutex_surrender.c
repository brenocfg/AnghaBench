#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_11__ {int nest_behavior; scalar_t__ onlyownerrelease; } ;
struct TYPE_9__ {int nest_cnt; int /*<<< orphan*/  lock; TYPE_7__ atrrs; TYPE_2__* holder; int /*<<< orphan*/  wait_queue; } ;
typedef  TYPE_1__ lwp_mutex ;
struct TYPE_10__ {scalar_t__ res_cnt; scalar_t__ real_prio; scalar_t__ cur_prio; } ;
typedef  TYPE_2__ lwp_cntrl ;

/* Variables and functions */
#define  LWP_MUTEX_NEST_ACQUIRE 130 
#define  LWP_MUTEX_NEST_BLOCK 129 
#define  LWP_MUTEX_NEST_ERROR 128 
 int /*<<< orphan*/  LWP_MUTEX_NEST_NOTALLOWED ; 
 int /*<<< orphan*/  LWP_MUTEX_NOTOWNER ; 
 int /*<<< orphan*/  LWP_MUTEX_SUCCESSFUL ; 
 int /*<<< orphan*/  LWP_MUTEX_UNLOCKED ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ __lwp_mutex_isinheritprio (TYPE_7__*) ; 
 scalar_t__ __lwp_mutex_isprioceiling (TYPE_7__*) ; 
 int /*<<< orphan*/  __lwp_thread_changepriority (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_isexec (TYPE_2__*) ; 
 TYPE_2__* __lwp_threadqueue_dequeue (int /*<<< orphan*/ *) ; 

u32 __lwp_mutex_surrender(lwp_mutex *mutex)
{
	lwp_cntrl *thethread;
	lwp_cntrl *holder;

	holder = mutex->holder;

	if(mutex->atrrs.onlyownerrelease) {
		if(!__lwp_thread_isexec(holder))
			return LWP_MUTEX_NOTOWNER;
	}

	if(!mutex->nest_cnt)
		return LWP_MUTEX_SUCCESSFUL;

	mutex->nest_cnt--;
	if(mutex->nest_cnt!=0) {
		switch(mutex->atrrs.nest_behavior) {
			case LWP_MUTEX_NEST_ACQUIRE:
				return LWP_MUTEX_SUCCESSFUL;
			case LWP_MUTEX_NEST_ERROR:
				return LWP_MUTEX_NEST_NOTALLOWED;
			case LWP_MUTEX_NEST_BLOCK:
				break;
		}
	}

	if(__lwp_mutex_isinheritprio(&mutex->atrrs) || __lwp_mutex_isprioceiling(&mutex->atrrs))
		holder->res_cnt--;

	mutex->holder = NULL;
	if(__lwp_mutex_isinheritprio(&mutex->atrrs) || __lwp_mutex_isprioceiling(&mutex->atrrs)) {
		if(holder->res_cnt==0 && holder->real_prio!=holder->cur_prio)
			__lwp_thread_changepriority(holder,holder->real_prio,TRUE);
	}

	if((thethread=__lwp_threadqueue_dequeue(&mutex->wait_queue))) {
		mutex->nest_cnt = 1;
		mutex->holder = thethread;
		if(__lwp_mutex_isinheritprio(&mutex->atrrs) || __lwp_mutex_isprioceiling(&mutex->atrrs))
			thethread->res_cnt++;
	} else
		mutex->lock = LWP_MUTEX_UNLOCKED;

	return LWP_MUTEX_SUCCESSFUL;
}