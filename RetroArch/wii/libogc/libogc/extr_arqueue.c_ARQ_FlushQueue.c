#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;

/* Variables and functions */
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ARQCallbackLo ; 
 int /*<<< orphan*/ * __ARQReqPendingLo ; 
 int /*<<< orphan*/  __ARQReqQueueHi ; 
 int /*<<< orphan*/  __ARQReqQueueLo ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 

void ARQ_FlushQueue()
{
	u32 level;

	_CPU_ISR_Disable(level);

	__lwp_queue_init_empty(&__ARQReqQueueLo);
	__lwp_queue_init_empty(&__ARQReqQueueHi);
	if(!__ARQCallbackLo) __ARQReqPendingLo = NULL;

	_CPU_ISR_Restore(level);
}