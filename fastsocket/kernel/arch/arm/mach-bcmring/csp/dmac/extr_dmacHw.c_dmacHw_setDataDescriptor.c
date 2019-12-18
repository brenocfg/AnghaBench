#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int dmacHw_TRANSACTION_WIDTH_e ;
struct TYPE_8__ {int hi; int lo; } ;
struct TYPE_9__ {int sar; int dar; scalar_t__ llp; TYPE_1__ ctl; scalar_t__ devCtl; } ;
typedef  TYPE_2__ dmacHw_DESC_t ;
struct TYPE_10__ {int num; TYPE_2__* pHead; TYPE_2__* pTail; TYPE_2__* pEnd; TYPE_2__* pProg; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;
struct TYPE_11__ {int dstMaxTransactionWidth; int srcMaxTransactionWidth; int srcGatherWidth; int dstScatterWidth; int maxDataPerBlock; int transferType; scalar_t__ flowControler; int srcUpdate; int dstUpdate; int srcMaxBurstWidth; int dstMaxBurstWidth; int srcMasterInterface; int dstMasterInterface; int dstScatterJump; int srcGatherJump; } ;
typedef  TYPE_4__ dmacHw_CONFIG_t ;

/* Variables and functions */
 int dmacHw_ADDRESS_MASK (int) ; 
 int /*<<< orphan*/  dmacHw_ASSERT (int) ; 
 int dmacHw_DESC_FREE ; 
 TYPE_2__* dmacHw_DESC_INIT ; 
 int /*<<< orphan*/  dmacHw_DST_IS_MEMORY (int) ; 
 int dmacHw_DST_TRANSACTION_WIDTH_8 ; 
 scalar_t__ dmacHw_FLOW_CONTROL_DMA ; 
 scalar_t__ dmacHw_FREE_USER_MEMORY ; 
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 int dmacHw_GetNextTrWidth (int) ; 
 int dmacHw_GetTrWidthInBytes (int) ; 
 int dmacHw_MAX_BLOCKSIZE ; 
 int dmacHw_REG_CTL_BLOCK_TS_MASK ; 
 int dmacHw_REG_CTL_DS_ENABLE ; 
 int dmacHw_REG_CTL_INT_EN ; 
 int dmacHw_REG_CTL_LLP_DST_EN ; 
 int dmacHw_REG_CTL_LLP_SRC_EN ; 
 int dmacHw_REG_CTL_SG_ENABLE ; 
 int dmacHw_REG_CTL_TTFC_MP_PERI ; 
 int dmacHw_REG_CTL_TTFC_PM_PERI ; 
 int dmacHw_SRC_TRANSACTION_WIDTH_8 ; 
#define  dmacHw_TRANSFER_TYPE_MEM_TO_MEM 131 
#define  dmacHw_TRANSFER_TYPE_MEM_TO_PERIPHERAL 130 
#define  dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM 129 
#define  dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_PERIPHERAL 128 

int dmacHw_setDataDescriptor(dmacHw_CONFIG_t *pConfig,	/*   [ IN ] Configuration settings */
			     void *pDescriptor,	/*   [ IN ] Descriptor buffer */
			     void *pSrcAddr,	/*   [ IN ] Source (Peripheral/Memory) address */
			     void *pDstAddr,	/*   [ IN ] Destination (Peripheral/Memory) address */
			     size_t dataLen	/*   [ IN ] Data length in bytes */
    ) {
	dmacHw_TRANSACTION_WIDTH_e dstTrWidth;
	dmacHw_TRANSACTION_WIDTH_e srcTrWidth;
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);
	dmacHw_DESC_t *pStart;
	dmacHw_DESC_t *pProg;
	int srcTs = 0;
	int blkTs = 0;
	int oddSize = 0;
	int descCount = 0;
	int count = 0;
	int dstTrSize = 0;
	int srcTrSize = 0;
	uint32_t maxBlockSize = dmacHw_MAX_BLOCKSIZE;

	dstTrSize = dmacHw_GetTrWidthInBytes(pConfig->dstMaxTransactionWidth);
	srcTrSize = dmacHw_GetTrWidthInBytes(pConfig->srcMaxTransactionWidth);

	/* Skip Tx if buffer is NULL  or length is unknown */
	if ((pSrcAddr == NULL) || (pDstAddr == NULL) || (dataLen == 0)) {
		/* Do not initiate transfer */
		return -1;
	}

	/* Ensure scatter and gather are transaction aligned */
	if ((pConfig->srcGatherWidth % srcTrSize)
	    || (pConfig->dstScatterWidth % dstTrSize)) {
		return -2;
	}

	/*
	   Background 1: DMAC can not perform DMA if source and destination addresses are
	   not properly aligned with the channel's transaction width. So, for successful
	   DMA transfer, transaction width must be set according to the alignment of the
	   source and destination address.
	 */

	/* Adjust destination transaction width if destination address is not aligned properly */
	dstTrWidth = pConfig->dstMaxTransactionWidth;
	while (dmacHw_ADDRESS_MASK(dstTrSize) & (uint32_t) pDstAddr) {
		dstTrWidth = dmacHw_GetNextTrWidth(dstTrWidth);
		dstTrSize = dmacHw_GetTrWidthInBytes(dstTrWidth);
	}

	/* Adjust source transaction width if source address is not aligned properly */
	srcTrWidth = pConfig->srcMaxTransactionWidth;
	while (dmacHw_ADDRESS_MASK(srcTrSize) & (uint32_t) pSrcAddr) {
		srcTrWidth = dmacHw_GetNextTrWidth(srcTrWidth);
		srcTrSize = dmacHw_GetTrWidthInBytes(srcTrWidth);
	}

	/* Find the maximum transaction per descriptor */
	if (pConfig->maxDataPerBlock
	    && ((pConfig->maxDataPerBlock / srcTrSize) <
		dmacHw_MAX_BLOCKSIZE)) {
		maxBlockSize = pConfig->maxDataPerBlock / srcTrSize;
	}

	/* Find number of source transactions needed to complete the DMA transfer */
	srcTs = dataLen / srcTrSize;
	/* Find the odd number of bytes that need to be transferred as single byte transaction width */
	if (srcTs && (dstTrSize > srcTrSize)) {
		oddSize = dataLen % dstTrSize;
		/* Adjust source transaction count due to "oddSize" */
		srcTs = srcTs - (oddSize / srcTrSize);
	} else {
		oddSize = dataLen % srcTrSize;
	}
	/* Adjust "descCount" due to "oddSize" */
	if (oddSize) {
		descCount++;
	}
	/* Find the number of descriptor needed for total "srcTs" */
	if (srcTs) {
		descCount += ((srcTs - 1) / maxBlockSize) + 1;
	}

	/* Check the availability of "descCount" discriptors in the ring */
	pProg = pRing->pHead;
	for (count = 0; (descCount <= pRing->num) && (count < descCount);
	     count++) {
		if ((pProg->ctl.hi & dmacHw_DESC_FREE) == 0) {
			/* Sufficient descriptors are not available */
			return -3;
		}
		pProg = (dmacHw_DESC_t *) pProg->llp;
	}

	/* Remember the link list item to program the channel registers */
	pStart = pProg = pRing->pHead;
	/* Make a link list with "descCount(=count)" number of descriptors */
	while (count) {
		/* Reset channel control information */
		pProg->ctl.lo = 0;
		/* Enable source gather if configured */
		if (pConfig->srcGatherWidth) {
			pProg->ctl.lo |= dmacHw_REG_CTL_SG_ENABLE;
		}
		/* Enable destination scatter if configured */
		if (pConfig->dstScatterWidth) {
			pProg->ctl.lo |= dmacHw_REG_CTL_DS_ENABLE;
		}
		/* Set source and destination address */
		pProg->sar = (uint32_t) pSrcAddr;
		pProg->dar = (uint32_t) pDstAddr;
		/* Use "devCtl" to mark that user memory need to be freed later if needed */
		if (pProg == pRing->pHead) {
			pProg->devCtl = dmacHw_FREE_USER_MEMORY;
		} else {
			pProg->devCtl = 0;
		}

		blkTs = srcTs;

		/* Special treatmeant for last descriptor */
		if (count == 1) {
			/* Mark the last descriptor */
			pProg->ctl.lo &=
			    ~(dmacHw_REG_CTL_LLP_DST_EN |
			      dmacHw_REG_CTL_LLP_SRC_EN);
			/* Treatment for odd data bytes */
			if (oddSize) {
				/* Adjust for single byte transaction width */
				switch (pConfig->transferType) {
				case dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM:
					dstTrWidth =
					    dmacHw_DST_TRANSACTION_WIDTH_8;
					blkTs =
					    (oddSize / srcTrSize) +
					    ((oddSize % srcTrSize) ? 1 : 0);
					break;
				case dmacHw_TRANSFER_TYPE_MEM_TO_PERIPHERAL:
					srcTrWidth =
					    dmacHw_SRC_TRANSACTION_WIDTH_8;
					blkTs = oddSize;
					break;
				case dmacHw_TRANSFER_TYPE_MEM_TO_MEM:
					srcTrWidth =
					    dmacHw_SRC_TRANSACTION_WIDTH_8;
					dstTrWidth =
					    dmacHw_DST_TRANSACTION_WIDTH_8;
					blkTs = oddSize;
					break;
				case dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_PERIPHERAL:
					/* Do not adjust the transaction width  */
					break;
				}
			} else {
				srcTs -= blkTs;
			}
		} else {
			if (srcTs / maxBlockSize) {
				blkTs = maxBlockSize;
			}
			/* Remaining source transactions for next iteration */
			srcTs -= blkTs;
		}
		/* Must have a valid source transactions */
		dmacHw_ASSERT(blkTs > 0);
		/* Set control information */
		if (pConfig->flowControler == dmacHw_FLOW_CONTROL_DMA) {
			pProg->ctl.lo |= pConfig->transferType |
			    pConfig->srcUpdate |
			    pConfig->dstUpdate |
			    srcTrWidth |
			    dstTrWidth |
			    pConfig->srcMaxBurstWidth |
			    pConfig->dstMaxBurstWidth |
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
			pProg->ctl.lo |= transferType |
			    pConfig->srcUpdate |
			    pConfig->dstUpdate |
			    srcTrWidth |
			    dstTrWidth |
			    pConfig->srcMaxBurstWidth |
			    pConfig->dstMaxBurstWidth |
			    pConfig->srcMasterInterface |
			    pConfig->dstMasterInterface | dmacHw_REG_CTL_INT_EN;
		}

		/* Set block transaction size */
		pProg->ctl.hi = blkTs & dmacHw_REG_CTL_BLOCK_TS_MASK;
		/* Look for next descriptor */
		if (count > 1) {
			/* Point to the next descriptor */
			pProg = (dmacHw_DESC_t *) pProg->llp;

			/* Update source and destination address for next iteration */
			switch (pConfig->transferType) {
			case dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_MEM:
				if (pConfig->dstScatterWidth) {
					pDstAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize +
					    (((blkTs * srcTrSize) /
					      pConfig->dstScatterWidth) *
					     pConfig->dstScatterJump);
				} else {
					pDstAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize;
				}
				break;
			case dmacHw_TRANSFER_TYPE_MEM_TO_PERIPHERAL:
				if (pConfig->srcGatherWidth) {
					pSrcAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize +
					    (((blkTs * srcTrSize) /
					      pConfig->srcGatherWidth) *
					     pConfig->srcGatherJump);
				} else {
					pSrcAddr =
					    (char *)pSrcAddr +
					    blkTs * srcTrSize;
				}
				break;
			case dmacHw_TRANSFER_TYPE_MEM_TO_MEM:
				if (pConfig->dstScatterWidth) {
					pDstAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize +
					    (((blkTs * srcTrSize) /
					      pConfig->dstScatterWidth) *
					     pConfig->dstScatterJump);
				} else {
					pDstAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize;
				}

				if (pConfig->srcGatherWidth) {
					pSrcAddr =
					    (char *)pDstAddr +
					    blkTs * srcTrSize +
					    (((blkTs * srcTrSize) /
					      pConfig->srcGatherWidth) *
					     pConfig->srcGatherJump);
				} else {
					pSrcAddr =
					    (char *)pSrcAddr +
					    blkTs * srcTrSize;
				}
				break;
			case dmacHw_TRANSFER_TYPE_PERIPHERAL_TO_PERIPHERAL:
				/* Do not adjust the address */
				break;
			default:
				dmacHw_ASSERT(0);
			}
		} else {
			/* At the end of transfer "srcTs" must be zero */
			dmacHw_ASSERT(srcTs == 0);
		}
		count--;
	}

	/* Remember the descriptor to initialize the registers */
	if (pRing->pProg == dmacHw_DESC_INIT) {
		pRing->pProg = pStart;
	}
	/* Indicate that the descriptor is updated */
	pRing->pEnd = pProg;
	/* Head pointing to the next descriptor */
	pRing->pHead = (dmacHw_DESC_t *) pProg->llp;
	/* Update Tail pointer if destination is a peripheral,
	   because no one is going to read from the pTail
	 */
	if (!dmacHw_DST_IS_MEMORY(pConfig->transferType)) {
		pRing->pTail = pRing->pHead;
	}
	return 0;
}