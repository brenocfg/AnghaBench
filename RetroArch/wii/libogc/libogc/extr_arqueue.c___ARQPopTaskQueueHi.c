#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  callback; int /*<<< orphan*/  len; int /*<<< orphan*/  aram_addr; int /*<<< orphan*/  mram_addr; int /*<<< orphan*/  dir; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ ARQRequest ;

/* Variables and functions */
 int /*<<< orphan*/  ARQ_TASK_RUNNING ; 
 int /*<<< orphan*/  AR_StartDMA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ARQCallbackHi ; 
 TYPE_1__* __ARQReqPendingHi ; 
 int /*<<< orphan*/  __ARQReqQueueHi ; 
 scalar_t__ __lwp_queue_getI (int /*<<< orphan*/ *) ; 

__attribute__((used)) static __inline__ void __ARQPopTaskQueueHi()
{
	ARQRequest *req;

	req = (ARQRequest*)__lwp_queue_getI(&__ARQReqQueueHi);
	if(!req) return;

	req->state = ARQ_TASK_RUNNING;
	AR_StartDMA(req->dir,req->mram_addr,req->aram_addr,req->len);
	__ARQCallbackHi = req->callback;
	__ARQReqPendingHi = req;
}