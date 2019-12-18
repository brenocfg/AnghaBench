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
struct TYPE_3__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  module; } ;
typedef  TYPE_1__ dmacHw_CBLK_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmacHw_DMA_STOP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 

void dmacHw_stopTransfer(dmacHw_HANDLE_t handle	/*   [ IN ] DMA Channel handle */
    ) {
	dmacHw_CBLK_t *pCblk;

	pCblk = dmacHw_HANDLE_TO_CBLK(handle);

	/* Stop the channel */
	dmacHw_DMA_STOP(pCblk->module, pCblk->channel);
}