#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct TYPE_2__ {int /*<<< orphan*/  BaseAddress; } ;
struct BusLogic_HostAdapter {int /*<<< orphan*/  AllocatedCCBs; struct BusLogic_CCB* All_CCBs; struct BusLogic_CCB* Free_CCBs; TYPE_1__ FlashPointInfo; } ;
struct BusLogic_CCB {int AllocationGroupSize; struct BusLogic_CCB* NextAll; struct BusLogic_CCB* Next; int /*<<< orphan*/  BaseAddress; int /*<<< orphan*/  CallbackFunction; scalar_t__ DMA_Handle; struct BusLogic_HostAdapter* HostAdapter; int /*<<< orphan*/  Status; scalar_t__ AllocationGroupHead; } ;
typedef  scalar_t__ dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  BusLogic_CCB_Free ; 
 scalar_t__ BusLogic_FlashPointHostAdapterP (struct BusLogic_HostAdapter*) ; 
 int /*<<< orphan*/  BusLogic_QueueCompletedCCB ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void BusLogic_InitializeCCBs(struct BusLogic_HostAdapter *HostAdapter, void *BlockPointer, int BlockSize, dma_addr_t BlockPointerHandle)
{
	struct BusLogic_CCB *CCB = (struct BusLogic_CCB *) BlockPointer;
	unsigned int offset = 0;
	memset(BlockPointer, 0, BlockSize);
	CCB->AllocationGroupHead = BlockPointerHandle;
	CCB->AllocationGroupSize = BlockSize;
	while ((BlockSize -= sizeof(struct BusLogic_CCB)) >= 0) {
		CCB->Status = BusLogic_CCB_Free;
		CCB->HostAdapter = HostAdapter;
		CCB->DMA_Handle = (u32) BlockPointerHandle + offset;
		if (BusLogic_FlashPointHostAdapterP(HostAdapter)) {
			CCB->CallbackFunction = BusLogic_QueueCompletedCCB;
			CCB->BaseAddress = HostAdapter->FlashPointInfo.BaseAddress;
		}
		CCB->Next = HostAdapter->Free_CCBs;
		CCB->NextAll = HostAdapter->All_CCBs;
		HostAdapter->Free_CCBs = CCB;
		HostAdapter->All_CCBs = CCB;
		HostAdapter->AllocatedCCBs++;
		CCB++;
		offset += sizeof(struct BusLogic_CCB);
	}
}