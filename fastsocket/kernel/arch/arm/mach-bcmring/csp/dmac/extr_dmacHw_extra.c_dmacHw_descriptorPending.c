#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
struct TYPE_5__ {scalar_t__ pEnd; } ;
typedef  TYPE_1__ dmacHw_DESC_RING_t ;
struct TYPE_6__ {int /*<<< orphan*/  channel; int /*<<< orphan*/  module; } ;
typedef  TYPE_2__ dmacHw_CBLK_t ;

/* Variables and functions */
 int /*<<< orphan*/  CHANNEL_BUSY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dmacHw_GET_DESC_RING (void*) ; 
 TYPE_2__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 

uint32_t dmacHw_descriptorPending(dmacHw_HANDLE_t handle,	/*   [ IN ] DMA Channel handle */
				  void *pDescriptor	/*   [ IN ] Descriptor buffer */
    ) {
	dmacHw_CBLK_t *pCblk = dmacHw_HANDLE_TO_CBLK(handle);
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);

	/* Make sure channel is not busy */
	if (!CHANNEL_BUSY(pCblk->module, pCblk->channel)) {
		/* Check if pEnd is not processed */
		if (pRing->pEnd) {
			/* Something left for processing */
			return 1;
		}
	}
	return 0;
}