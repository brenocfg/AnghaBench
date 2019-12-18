#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_8__ {int /*<<< orphan*/  fifo; } ;
struct TYPE_9__ {int sync_state; TYPE_1__ queues; } ;
typedef  TYPE_2__ lwp_thrqueue ;
struct TYPE_10__ {int /*<<< orphan*/  timer; } ;
typedef  TYPE_3__ lwp_cntrl ;

/* Variables and functions */
#define  LWP_THREADQ_NOTHINGHAPPEND 131 
#define  LWP_THREADQ_SATISFIED 130 
#define  LWP_THREADQ_SYNCHRONIZED 129 
#define  LWP_THREADQ_TIMEOUT 128 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 scalar_t__ __lwp_queue_firstnodeI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_queue_isempty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_thread_unblock (TYPE_3__*) ; 
 int /*<<< orphan*/  __lwp_wd_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_isactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_remove_ticks (int /*<<< orphan*/ *) ; 
 TYPE_3__* _thr_executing ; 

lwp_cntrl* __lwp_threadqueue_dequeuefifo(lwp_thrqueue *queue)
{
	u32 level;
	lwp_cntrl *ret;

	_CPU_ISR_Disable(level);
	if(!__lwp_queue_isempty(&queue->queues.fifo)) {
		ret = (lwp_cntrl*)__lwp_queue_firstnodeI(&queue->queues.fifo);
		if(!__lwp_wd_isactive(&ret->timer)) {
			_CPU_ISR_Restore(level);
			__lwp_thread_unblock(ret);
		} else {
			__lwp_wd_deactivate(&ret->timer);
			_CPU_ISR_Restore(level);
			__lwp_wd_remove_ticks(&ret->timer);
			__lwp_thread_unblock(ret);
		}
		return ret;
	}

	switch(queue->sync_state) {
		case LWP_THREADQ_SYNCHRONIZED:
		case LWP_THREADQ_SATISFIED:
			_CPU_ISR_Restore(level);
			return NULL;
		case LWP_THREADQ_NOTHINGHAPPEND:
		case LWP_THREADQ_TIMEOUT:
			queue->sync_state = LWP_THREADQ_SATISFIED;
			_CPU_ISR_Restore(level);
			return _thr_executing;
	}
	return NULL;
}