#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_7__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct TYPE_9__ {TYPE_7__* pHead; TYPE_7__* pTail; TYPE_7__* pEnd; TYPE_7__* pProg; } ;
typedef  TYPE_2__ dmacHw_DESC_RING_t ;
struct TYPE_10__ {scalar_t__ flowControler; scalar_t__ transferType; scalar_t__ dstMaxTransactionWidth; scalar_t__ srcMasterInterface; scalar_t__ dstMasterInterface; } ;
typedef  TYPE_3__ dmacHw_CONFIG_t ;
struct TYPE_8__ {int hi; scalar_t__ lo; } ;
struct TYPE_11__ {TYPE_1__ ctl; scalar_t__ dar; scalar_t__ devCtl; scalar_t__ sar; } ;

/* Variables and functions */
 int /*<<< orphan*/  dmacHw_ASSERT (int /*<<< orphan*/ ) ; 
 int dmacHw_DESC_FREE ; 
 TYPE_7__* dmacHw_DESC_INIT ; 
 scalar_t__ dmacHw_DST_ADDRESS_UPDATE_MODE_INC ; 
 scalar_t__ dmacHw_DST_BURST_WIDTH_0 ; 
 int /*<<< orphan*/  dmacHw_DST_IS_MEMORY (int) ; 
 scalar_t__ dmacHw_FLOW_CONTROL_DMA ; 
 TYPE_2__* dmacHw_GET_DESC_RING (void*) ; 
 int /*<<< orphan*/  dmacHw_NEXT_DESC (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dmacHw_REG_CTL_BLOCK_TS_MASK ; 
 scalar_t__ dmacHw_REG_CTL_INT_EN ; 
 scalar_t__ dmacHw_REG_CTL_TTFC_MP_PERI ; 
 scalar_t__ dmacHw_REG_CTL_TTFC_PM_PERI ; 
 scalar_t__ dmacHw_SRC_ADDRESS_UPDATE_MODE_INC ; 
 scalar_t__ dmacHw_SRC_BURST_WIDTH_0 ; 
 scalar_t__ dmacHw_SRC_TRANSACTION_WIDTH_32 ; 
#define  dmacHw_TRANSFER_TYPE_MEM_TO_PERIPHERAL 129 
#define  dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM 128 
 int /*<<< orphan*/  pHead ; 

int dmacHw_setControlDescriptor(dmacHw_CONFIG_t *pConfig,	/*   [ IN ] Configuration settings */
				void *pDescriptor,	/*   [ IN ] Descriptor buffer */
				uint32_t ctlAddress,	/*   [ IN ] Address of the device control register */
				uint32_t control	/*   [ IN ] Device control information */
    ) {
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);

	if (ctlAddress == 0) {
		return -1;
	}

	/* Check the availability of descriptors in the ring */
	if ((pRing->pHead->ctl.hi & dmacHw_DESC_FREE) == 0) {
		return -1;
	}
	/* Set control information */
	pRing->pHead->devCtl = control;
	/* Set source and destination address */
	pRing->pHead->sar = (uint32_t) &pRing->pHead->devCtl;
	pRing->pHead->dar = ctlAddress;
	/* Set control parameters */
	if (pConfig->flowControler == dmacHw_FLOW_CONTROL_DMA) {
		pRing->pHead->ctl.lo = pConfig->transferType |
		    dmacHw_SRC_ADDRESS_UPDATE_MODE_INC |
		    dmacHw_DST_ADDRESS_UPDATE_MODE_INC |
		    dmacHw_SRC_TRANSACTION_WIDTH_32 |
		    pConfig->dstMaxTransactionWidth |
		    dmacHw_SRC_BURST_WIDTH_0 |
		    dmacHw_DST_BURST_WIDTH_0 |
		    pConfig->srcMasterInterface |
		    pConfig->dstMasterInterface | dmacHw_REG_CTL_INT_EN;
	} else {
		uint32_t transferType = 0;
		switch (pConfig->transferType) {
		case dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM:
			transferType = dmacHw_REG_CTL_TTFC_PM_PERI;
			break;
		case dmacHw_TRANSFER_TYPE_MEM_TO_PERIPHERAL:
			transferType = dmacHw_REG_CTL_TTFC_MP_PERI;
			break;
		default:
			dmacHw_ASSERT(0);
		}
		pRing->pHead->ctl.lo = transferType |
		    dmacHw_SRC_ADDRESS_UPDATE_MODE_INC |
		    dmacHw_DST_ADDRESS_UPDATE_MODE_INC |
		    dmacHw_SRC_TRANSACTION_WIDTH_32 |
		    pConfig->dstMaxTransactionWidth |
		    dmacHw_SRC_BURST_WIDTH_0 |
		    dmacHw_DST_BURST_WIDTH_0 |
		    pConfig->srcMasterInterface |
		    pConfig->dstMasterInterface |
		    pConfig->flowControler | dmacHw_REG_CTL_INT_EN;
	}

	/* Set block transaction size to one 32 bit transaction */
	pRing->pHead->ctl.hi = dmacHw_REG_CTL_BLOCK_TS_MASK & 1;

	/* Remember the descriptor to initialize the registers */
	if (pRing->pProg == dmacHw_DESC_INIT) {
		pRing->pProg = pRing->pHead;
	}
	pRing->pEnd = pRing->pHead;

	/* Advance the descriptor */
	dmacHw_NEXT_DESC(pRing, pHead);

	/* Update Tail pointer if destination is a peripheral */
	if (!dmacHw_DST_IS_MEMORY(pConfig->transferType)) {
		pRing->pTail = pRing->pHead;
	}
	return 0;
}