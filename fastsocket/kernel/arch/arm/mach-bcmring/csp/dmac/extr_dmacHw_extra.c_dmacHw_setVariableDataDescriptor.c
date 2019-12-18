#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
struct TYPE_10__ {int hi; scalar_t__ lo; } ;
struct TYPE_11__ {TYPE_1__ ctl; int /*<<< orphan*/  devCtl; scalar_t__ dar; scalar_t__ sar; scalar_t__ llp; } ;
typedef  TYPE_2__ dmacHw_DESC_t ;
struct TYPE_12__ {int num; scalar_t__ virt2PhyOffset; TYPE_2__* pEnd; TYPE_2__* pHead; TYPE_2__* pTail; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;
struct TYPE_13__ {scalar_t__ transferType; scalar_t__ srcUpdate; scalar_t__ dstUpdate; scalar_t__ srcMaxTransactionWidth; scalar_t__ dstMaxTransactionWidth; scalar_t__ srcMasterInterface; scalar_t__ dstMasterInterface; scalar_t__ srcMaxBurstWidth; scalar_t__ dstMaxBurstWidth; } ;
typedef  TYPE_4__ dmacHw_CONFIG_t ;
struct TYPE_14__ {int descUpdated; int varDataStarted; int /*<<< orphan*/  channel; int /*<<< orphan*/  module; } ;
typedef  TYPE_5__ dmacHw_CBLK_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmacHw_ASSERT (int) ; 
 int dmacHw_DESC_FREE ; 
 int /*<<< orphan*/  dmacHw_FREE_USER_MEMORY ; 
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 TYPE_5__* dmacHw_HANDLE_TO_CBLK (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmacHw_NEXT_DESC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ dmacHw_REG_CTL_INT_EN ; 
 scalar_t__ dmacHw_REG_CTL_LLP_DST_EN ; 
 scalar_t__ dmacHw_REG_CTL_LLP_SRC_EN ; 
 scalar_t__ dmacHw_REG_CTL_TTFC_PM_PERI ; 
 int /*<<< orphan*/  dmacHw_SET_LLP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM ; 
 int /*<<< orphan*/  pHead ; 
 void* stub1 (int) ; 

int dmacHw_setVariableDataDescriptor(dmacHw_HANDLE_t handle,	/*   [ IN ] DMA Channel handle */
				     dmacHw_CONFIG_t *pConfig,	/*   [ IN ] Configuration settings */
				     void *pDescriptor,	/*   [ IN ] Descriptor buffer */
				     uint32_t srcAddr,	/*   [ IN ] Source peripheral address */
				     void *(*fpAlloc) (int len),	/*   [ IN ] Function pointer  that provides destination memory */
				     int len,	/*   [ IN ] Number of bytes "fpAlloc" will allocate for destination */
				     int num	/*   [ IN ] Number of descriptor to set */
    ) {
	dmacHw_CBLK_t *pCblk = dmacHw_HANDLE_TO_CBLK(handle);
	dmacHw_DESC_t *pProg = NULL;
	dmacHw_DESC_t *pLast = NULL;
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);
	uint32_t dstAddr;
	uint32_t controlParam;
	int i;

	dmacHw_ASSERT(pConfig->transferType ==
		      dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM);

	if (num > pRing->num) {
		return -1;
	}

	pLast = pRing->pEnd;	/* Last descriptor updated */
	pProg = pRing->pHead;	/* First descriptor in the new list */

	controlParam = pConfig->srcUpdate |
	    pConfig->dstUpdate |
	    pConfig->srcMaxTransactionWidth |
	    pConfig->dstMaxTransactionWidth |
	    pConfig->srcMasterInterface |
	    pConfig->dstMasterInterface |
	    pConfig->srcMaxBurstWidth |
	    pConfig->dstMaxBurstWidth |
	    dmacHw_REG_CTL_TTFC_PM_PERI |
	    dmacHw_REG_CTL_LLP_DST_EN |
	    dmacHw_REG_CTL_LLP_SRC_EN | dmacHw_REG_CTL_INT_EN;

	for (i = 0; i < num; i++) {
		/* Allocate Rx buffer only for idle descriptor */
		if (((pRing->pHead->ctl.hi & dmacHw_DESC_FREE) == 0) ||
		    ((dmacHw_DESC_t *) pRing->pHead->llp == pRing->pTail)
		    ) {
			/* Rx descriptor is not idle */
			break;
		}
		/* Set source address */
		pRing->pHead->sar = srcAddr;
		if (fpAlloc) {
			/* Allocate memory for buffer in descriptor */
			dstAddr = (uint32_t) (*fpAlloc) (len);
			/* Check the destination address */
			if (dstAddr == 0) {
				if (i == 0) {
					/* Not a single descriptor is available */
					return -1;
				}
				break;
			}
			/* Set destination address */
			pRing->pHead->dar = dstAddr;
		}
		/* Set control information */
		pRing->pHead->ctl.lo = controlParam;
		/* Use "devCtl" to mark the memory that need to be freed later */
		pRing->pHead->devCtl = dmacHw_FREE_USER_MEMORY;
		/* Descriptor is now owned by the channel */
		pRing->pHead->ctl.hi = 0;
		/* Remember the descriptor last updated */
		pRing->pEnd = pRing->pHead;
		/* Update next descriptor */
		dmacHw_NEXT_DESC(pRing, pHead);
	}

	/* Mark the end of the list */
	pRing->pEnd->ctl.lo &=
	    ~(dmacHw_REG_CTL_LLP_DST_EN | dmacHw_REG_CTL_LLP_SRC_EN);
	/* Connect the list */
	if (pLast != pProg) {
		pLast->ctl.lo |=
		    dmacHw_REG_CTL_LLP_DST_EN | dmacHw_REG_CTL_LLP_SRC_EN;
	}
	/* Mark the descriptors are updated */
	pCblk->descUpdated = 1;
	if (!pCblk->varDataStarted) {
		/* LLP must be pointing to the first descriptor */
		dmacHw_SET_LLP(pCblk->module, pCblk->channel,
			       (uint32_t) pProg - pRing->virt2PhyOffset);
		/* Channel, handling variable data started */
		pCblk->varDataStarted = 1;
	}

	return i;
}