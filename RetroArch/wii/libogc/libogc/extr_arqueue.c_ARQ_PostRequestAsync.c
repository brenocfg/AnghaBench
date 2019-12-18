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
typedef  scalar_t__ u32 ;
struct TYPE_4__ {int /*<<< orphan*/ * callback; scalar_t__ len; scalar_t__ aram_addr; scalar_t__ mram_addr; scalar_t__ dir; int /*<<< orphan*/  state; int /*<<< orphan*/  node; scalar_t__ prio; scalar_t__ owner; } ;
typedef  TYPE_1__ ARQRequest ;
typedef  int /*<<< orphan*/ * ARQCallback ;

/* Variables and functions */
 scalar_t__ ARQ_PRIO_LO ; 
 int /*<<< orphan*/  ARQ_TASK_READY ; 
 int /*<<< orphan*/  ARQ_TASK_RUNNING ; 
 int /*<<< orphan*/  AR_StartDMA (scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 int /*<<< orphan*/ * __ARQCallbackDummy ; 
 int /*<<< orphan*/ * __ARQCallbackHi ; 
 TYPE_1__* __ARQReqPendingHi ; 
 int /*<<< orphan*/  __ARQReqPendingLo ; 
 int /*<<< orphan*/  __ARQReqQueueHi ; 
 int /*<<< orphan*/  __ARQReqQueueLo ; 
 int /*<<< orphan*/  __ARQServiceQueueLo () ; 
 int /*<<< orphan*/  __lwp_queue_appendI (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ __lwp_queue_getI (int /*<<< orphan*/ *) ; 

void ARQ_PostRequestAsync(ARQRequest *req,u32 owner,u32 dir,u32 prio,u32 aram_addr,u32 mram_addr,u32 len,ARQCallback cb)
{
	u32 level;
	ARQRequest *p;

	req->state = ARQ_TASK_READY;
	req->dir = dir;
	req->owner = owner;
	req->aram_addr = aram_addr;
	req->mram_addr = mram_addr;
	req->len = len;
	req->prio = prio;
	req->callback = (cb==NULL) ? __ARQCallbackDummy : cb;

	_CPU_ISR_Disable(level);

	if(prio==ARQ_PRIO_LO) __lwp_queue_appendI(&__ARQReqQueueLo,&req->node);
	else __lwp_queue_appendI(&__ARQReqQueueHi,&req->node);

	if(!__ARQReqPendingLo && !__ARQReqPendingHi) {
		p = (ARQRequest*)__lwp_queue_getI(&__ARQReqQueueHi);
		if(p) {
			p->state = ARQ_TASK_RUNNING;
			AR_StartDMA(p->dir,p->mram_addr,p->aram_addr,p->len);
			__ARQCallbackHi = p->callback;
			__ARQReqPendingHi = p;
		}
		if(!__ARQReqPendingHi) __ARQServiceQueueLo();
	}
	_CPU_ISR_Restore(level);
}