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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_4__ {int /*<<< orphan*/  node; } ;
typedef  TYPE_1__ ARQRequest ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __ARQCallbackLo ; 
 TYPE_1__* __ARQReqPendingLo ; 
 int /*<<< orphan*/  __lwp_queue_extractI (int /*<<< orphan*/ *) ; 

void ARQ_RemoveRequest(ARQRequest *req)
{
	u32 level;

	_CPU_ISR_Disable(level);
	__lwp_queue_extractI(&req->node);
	if(__ARQReqPendingLo && __ARQReqPendingLo==req && __ARQCallbackLo==NULL) __ARQReqPendingLo = NULL;
	_CPU_ISR_Restore(level);
}