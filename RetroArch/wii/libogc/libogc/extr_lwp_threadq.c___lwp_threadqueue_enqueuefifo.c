#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
typedef  int u32 ;
struct TYPE_11__ {int /*<<< orphan*/  fifo; } ;
struct TYPE_15__ {int sync_state; TYPE_1__ queues; } ;
typedef  TYPE_5__ lwp_thrqueue ;
struct TYPE_14__ {TYPE_3__* queue; int /*<<< orphan*/  ret_code; } ;
struct TYPE_12__ {int /*<<< orphan*/  node; } ;
struct TYPE_16__ {int /*<<< orphan*/  timer; TYPE_4__ wait; TYPE_2__ object; } ;
typedef  TYPE_6__ lwp_cntrl ;
struct TYPE_13__ {int /*<<< orphan*/  timeout_state; } ;

/* Variables and functions */
#define  LWP_THREADQ_NOTHINGHAPPEND 131 
#define  LWP_THREADQ_SATISFIED 130 
#define  LWP_THREADQ_SYNCHRONIZED 129 
#define  LWP_THREADQ_TIMEOUT 128 
 int /*<<< orphan*/  _CPU_ISR_Disable (int) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int) ; 
 int /*<<< orphan*/  __lwp_queue_appendI (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_thread_unblock (TYPE_6__*) ; 
 int /*<<< orphan*/  __lwp_wd_deactivate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_isactive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  __lwp_wd_remove_ticks (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,TYPE_6__*,int) ; 

void __lwp_threadqueue_enqueuefifo(lwp_thrqueue *queue,lwp_cntrl *thethread,u64 timeout)
{
	u32 level,sync_state;

	_CPU_ISR_Disable(level);

	sync_state = queue->sync_state;
	queue->sync_state = LWP_THREADQ_SYNCHRONIZED;
#ifdef _LWPTHRQ_DEBUG
	printf("__lwp_threadqueue_enqueuefifo(%p,%d)\n",thethread,sync_state);
#endif
	switch(sync_state) {
		case LWP_THREADQ_SYNCHRONIZED:
			break;
		case LWP_THREADQ_NOTHINGHAPPEND:
			__lwp_queue_appendI(&queue->queues.fifo,&thethread->object.node);
			_CPU_ISR_Restore(level);
			return;
		case LWP_THREADQ_TIMEOUT:
			thethread->wait.ret_code = thethread->wait.queue->timeout_state;
			_CPU_ISR_Restore(level);
			break;
		case LWP_THREADQ_SATISFIED:
			if(__lwp_wd_isactive(&thethread->timer)) {
				__lwp_wd_deactivate(&thethread->timer);
				_CPU_ISR_Restore(level);
				__lwp_wd_remove_ticks(&thethread->timer);
			} else
				_CPU_ISR_Restore(level);

			break;
	}
	__lwp_thread_unblock(thethread);
}