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
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
struct TYPE_3__ {int module; int channel; } ;
typedef  TYPE_1__ dmacHw_CBLK_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmacHw_BLOCK_INT_CLEAR (int,int) ; 
 int /*<<< orphan*/  dmacHw_BLOCK_INT_DISABLE (int,int) ; 
 int /*<<< orphan*/  dmacHw_DMA_ENABLE (int) ; 
 int /*<<< orphan*/  dmacHw_DTRAN_INT_DISABLE (int,int) ; 
 int /*<<< orphan*/  dmacHw_ERROR_INT_CLEAR (int,int) ; 
 int /*<<< orphan*/  dmacHw_ERROR_INT_DISABLE (int,int) ; 
 TYPE_1__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_RESET_CONFIG_HI (int,int) ; 
 int /*<<< orphan*/  dmacHw_RESET_CONFIG_LO (int,int) ; 
 int /*<<< orphan*/  dmacHw_RESET_CONTROL_HI (int,int) ; 
 int /*<<< orphan*/  dmacHw_RESET_CONTROL_LO (int,int) ; 
 int /*<<< orphan*/  dmacHw_STRAN_INT_DISABLE (int,int) ; 
 int /*<<< orphan*/  dmacHw_TRAN_INT_CLEAR (int,int) ; 
 int /*<<< orphan*/  dmacHw_TRAN_INT_DISABLE (int,int) ; 
 int /*<<< orphan*/  memset (void*,int /*<<< orphan*/ ,int) ; 

int dmacHw_initChannel(dmacHw_HANDLE_t handle	/*   [ IN ] DMA Channel handle */
    ) {
	dmacHw_CBLK_t *pCblk = dmacHw_HANDLE_TO_CBLK(handle);
	int module = pCblk->module;
	int channel = pCblk->channel;

	/* Reinitialize the control block */
	memset((void *)pCblk, 0, sizeof(dmacHw_CBLK_t));
	pCblk->module = module;
	pCblk->channel = channel;

	/* Enable DMA controller */
	dmacHw_DMA_ENABLE(pCblk->module);
	/* Reset DMA channel */
	dmacHw_RESET_CONTROL_LO(pCblk->module, pCblk->channel);
	dmacHw_RESET_CONTROL_HI(pCblk->module, pCblk->channel);
	dmacHw_RESET_CONFIG_LO(pCblk->module, pCblk->channel);
	dmacHw_RESET_CONFIG_HI(pCblk->module, pCblk->channel);

	/* Clear all raw interrupt status */
	dmacHw_TRAN_INT_CLEAR(pCblk->module, pCblk->channel);
	dmacHw_BLOCK_INT_CLEAR(pCblk->module, pCblk->channel);
	dmacHw_ERROR_INT_CLEAR(pCblk->module, pCblk->channel);

	/* Mask event specific interrupts */
	dmacHw_TRAN_INT_DISABLE(pCblk->module, pCblk->channel);
	dmacHw_BLOCK_INT_DISABLE(pCblk->module, pCblk->channel);
	dmacHw_STRAN_INT_DISABLE(pCblk->module, pCblk->channel);
	dmacHw_DTRAN_INT_DISABLE(pCblk->module, pCblk->channel);
	dmacHw_ERROR_INT_DISABLE(pCblk->module, pCblk->channel);

	return 0;
}