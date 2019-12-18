#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ next; } ;
struct TYPE_8__ {scalar_t__ first; } ;
struct TYPE_7__ {scalar_t__ owner; TYPE_3__ node; } ;
typedef  TYPE_1__ ARQRequest ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (scalar_t__) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (scalar_t__) ; 
 int /*<<< orphan*/ * __ARQCallbackLo ; 
 TYPE_1__* __ARQReqPendingLo ; 
 TYPE_2__ __ARQReqQueueHi ; 
 TYPE_2__ __ARQReqQueueLo ; 
 int /*<<< orphan*/  __lwp_queue_extractI (TYPE_3__*) ; 
 scalar_t__ __lwp_queue_tail (TYPE_2__*) ; 

u32 ARQ_RemoveOwnerRequest(u32 owner)
{
	u32 level,cnt;
	ARQRequest *req;

	_CPU_ISR_Disable(level);

	cnt = 0;
	req = (ARQRequest*)__ARQReqQueueHi.first;
	while(req!=(ARQRequest*)__lwp_queue_tail(&__ARQReqQueueHi)) {
		if(req->owner==owner) {
			__lwp_queue_extractI(&req->node);
			cnt++;
		}
		req = (ARQRequest*)req->node.next;
	}

	req = (ARQRequest*)__ARQReqQueueLo.first;
	while(req!=(ARQRequest*)__lwp_queue_tail(&__ARQReqQueueLo)) {
		if(req->owner==owner) {
			__lwp_queue_extractI(&req->node);
			cnt++;
		}
		req = (ARQRequest*)req->node.next;
	}
	if(__ARQReqPendingLo && __ARQReqPendingLo==req && __ARQCallbackLo==NULL) __ARQReqPendingLo = NULL;
	_CPU_ISR_Restore(level);

	return cnt;
}