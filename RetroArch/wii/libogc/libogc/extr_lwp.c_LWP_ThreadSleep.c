#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  tqueue; } ;
typedef  TYPE_2__ tqueue_st ;
typedef  int s32 ;
typedef  int /*<<< orphan*/  lwpq_t ;
struct TYPE_6__ {int /*<<< orphan*/  id; int /*<<< orphan*/ * queue; int /*<<< orphan*/ * ret_arg_1; int /*<<< orphan*/ * ret_arg; scalar_t__ ret_code; } ;
struct TYPE_8__ {TYPE_1__ wait; } ;
typedef  TYPE_3__ lwp_cntrl ;

/* Variables and functions */
 int /*<<< orphan*/  LWP_THREADQ_NOTIMEOUT ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __lwp_thread_dispatchenable () ; 
 int /*<<< orphan*/  __lwp_threadqueue_csenter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_threadqueue_enqueue (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_2__* __lwp_tqueue_open (int /*<<< orphan*/ ) ; 
 TYPE_3__* _thr_executing ; 

s32 LWP_ThreadSleep(lwpq_t thequeue)
{
	u32 level;
	tqueue_st *tq;
	lwp_cntrl *exec = NULL;

	tq = __lwp_tqueue_open(thequeue);
	if(!tq) return -1;

	exec = _thr_executing;
	_CPU_ISR_Disable(level);
	__lwp_threadqueue_csenter(&tq->tqueue);
	exec->wait.ret_code = 0;
	exec->wait.ret_arg = NULL;
	exec->wait.ret_arg_1 = NULL;
	exec->wait.queue = &tq->tqueue;
	exec->wait.id = thequeue;
	_CPU_ISR_Restore(level);
	__lwp_threadqueue_enqueue(&tq->tqueue,LWP_THREADQ_NOTIMEOUT);
	__lwp_thread_dispatchenable();
	return 0;
}