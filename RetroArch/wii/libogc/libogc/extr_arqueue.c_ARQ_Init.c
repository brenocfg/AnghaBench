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
 int /*<<< orphan*/  ARQ_DEF_CHUNK_SIZE ; 
 int /*<<< orphan*/  AR_RegisterCallback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWP_InitQueue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _CPU_ISR_Disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _CPU_ISR_Restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __ARInterruptServiceRoutine ; 
 int /*<<< orphan*/ * __ARQCallbackHi ; 
 int /*<<< orphan*/ * __ARQCallbackLo ; 
 int /*<<< orphan*/  __ARQChunkSize ; 
 int __ARQInitFlag ; 
 int /*<<< orphan*/ * __ARQReqPendingHi ; 
 int /*<<< orphan*/ * __ARQReqPendingLo ; 
 int /*<<< orphan*/  __ARQReqQueueHi ; 
 int /*<<< orphan*/  __ARQReqQueueLo ; 
 int /*<<< orphan*/  __ARQSyncQueue ; 
 int /*<<< orphan*/  __lwp_queue_init_empty (int /*<<< orphan*/ *) ; 

void ARQ_Init()
{
	u32 level;
	if(__ARQInitFlag) return;

	_CPU_ISR_Disable(level);

	__ARQReqPendingLo = NULL;
	__ARQReqPendingHi = NULL;
	__ARQCallbackLo = NULL;
	__ARQCallbackHi = NULL;

	__ARQChunkSize = ARQ_DEF_CHUNK_SIZE;

	LWP_InitQueue(&__ARQSyncQueue);

	__lwp_queue_init_empty(&__ARQReqQueueLo);
	__lwp_queue_init_empty(&__ARQReqQueueHi);

	AR_RegisterCallback(__ARInterruptServiceRoutine);

	__ARQInitFlag = 1;
	_CPU_ISR_Restore(level);
}