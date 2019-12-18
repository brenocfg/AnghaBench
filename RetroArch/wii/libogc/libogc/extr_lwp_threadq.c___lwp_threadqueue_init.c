#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int u32 ;
struct TYPE_5__ {int /*<<< orphan*/ * priority; int /*<<< orphan*/  fifo; } ;
struct TYPE_6__ {int state; int mode; int timeout_state; TYPE_1__ queues; int /*<<< orphan*/  sync_state; } ;
typedef  TYPE_2__ lwp_thrqueue ;

/* Variables and functions */
#define  LWP_THREADQ_MODEFIFO 129 
#define  LWP_THREADQ_MODEPRIORITY 128 
 int LWP_THREADQ_NUM_PRIOHEADERS ; 
 int /*<<< orphan*/  LWP_THREADQ_SYNCHRONIZED ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  printf (char*,TYPE_2__*,int,int,int) ; 

void __lwp_threadqueue_init(lwp_thrqueue *queue,u32 mode,u32 state,u32 timeout_state)
{
	u32 index;

	queue->state = state;
	queue->mode = mode;
	queue->timeout_state = timeout_state;
	queue->sync_state = LWP_THREADQ_SYNCHRONIZED;
#ifdef _LWPTHRQ_DEBUG
	printf("__lwp_threadqueue_init(%p,%08x,%d,%d)\n",queue,state,timeout_state,mode);
#endif
	switch(mode) {
		case LWP_THREADQ_MODEFIFO:
			__lwp_queue_init_empty(&queue->queues.fifo);
			break;
		case LWP_THREADQ_MODEPRIORITY:
			for(index=0;index<LWP_THREADQ_NUM_PRIOHEADERS;index++)
				__lwp_queue_init_empty(&queue->queues.priority[index]);
			break;
	}
}