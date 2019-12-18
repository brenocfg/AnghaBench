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
typedef  int /*<<< orphan*/  dmacHw_INTERRUPT_STATUS_e ;
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
struct TYPE_3__ {int channel; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ dmacHw_CBLK_t ;

/* Variables and functions */
 TYPE_1__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_INTERRUPT_STATUS_BLOCK ; 
 int /*<<< orphan*/  dmacHw_INTERRUPT_STATUS_ERROR ; 
 int /*<<< orphan*/  dmacHw_INTERRUPT_STATUS_NONE ; 
 int /*<<< orphan*/  dmacHw_INTERRUPT_STATUS_TRANS ; 
 int dmacHw_REG_INT_STAT_BLOCK (int /*<<< orphan*/ ) ; 
 int dmacHw_REG_INT_STAT_ERROR (int /*<<< orphan*/ ) ; 
 int dmacHw_REG_INT_STAT_TRAN (int /*<<< orphan*/ ) ; 

dmacHw_INTERRUPT_STATUS_e dmacHw_getInterruptStatus(dmacHw_HANDLE_t handle	/* [ IN ] DMA Channel handle */
    ) {
	dmacHw_CBLK_t *pCblk = dmacHw_HANDLE_TO_CBLK(handle);
	dmacHw_INTERRUPT_STATUS_e status = dmacHw_INTERRUPT_STATUS_NONE;

	if (dmacHw_REG_INT_STAT_TRAN(pCblk->module) &
	    ((0x00000001 << pCblk->channel))) {
		status |= dmacHw_INTERRUPT_STATUS_TRANS;
	}
	if (dmacHw_REG_INT_STAT_BLOCK(pCblk->module) &
	    ((0x00000001 << pCblk->channel))) {
		status |= dmacHw_INTERRUPT_STATUS_BLOCK;
	}
	if (dmacHw_REG_INT_STAT_ERROR(pCblk->module) &
	    ((0x00000001 << pCblk->channel))) {
		status |= dmacHw_INTERRUPT_STATUS_ERROR;
	}

	return status;
}