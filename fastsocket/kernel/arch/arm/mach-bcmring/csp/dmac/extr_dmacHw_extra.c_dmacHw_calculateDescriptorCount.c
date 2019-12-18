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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  dmacHw_TRANSACTION_WIDTH_e ;
struct TYPE_3__ {int srcGatherWidth; int dstScatterWidth; int maxDataPerBlock; int /*<<< orphan*/  srcMaxTransactionWidth; int /*<<< orphan*/  dstMaxTransactionWidth; } ;
typedef  TYPE_1__ dmacHw_CONFIG_t ;

/* Variables and functions */
 int dmacHw_ADDRESS_MASK (int) ; 
 int /*<<< orphan*/  dmacHw_GetNextTrWidth (int /*<<< orphan*/ ) ; 
 int dmacHw_GetTrWidthInBytes (int /*<<< orphan*/ ) ; 
 int dmacHw_MAX_BLOCKSIZE ; 

int dmacHw_calculateDescriptorCount(dmacHw_CONFIG_t *pConfig,	/*   [ IN ] Configuration settings */
				    void *pSrcAddr,	/*   [ IN ] Source (Peripheral/Memory) address */
				    void *pDstAddr,	/*   [ IN ] Destination (Peripheral/Memory) address */
				    size_t dataLen	/*   [ IN ] Data length in bytes */
    ) {
	int srcTs = 0;
	int oddSize = 0;
	int descCount = 0;
	int dstTrSize = 0;
	int srcTrSize = 0;
	uint32_t maxBlockSize = dmacHw_MAX_BLOCKSIZE;
	dmacHw_TRANSACTION_WIDTH_e dstTrWidth;
	dmacHw_TRANSACTION_WIDTH_e srcTrWidth;

	dstTrSize = dmacHw_GetTrWidthInBytes(pConfig->dstMaxTransactionWidth);
	srcTrSize = dmacHw_GetTrWidthInBytes(pConfig->srcMaxTransactionWidth);

	/* Skip Tx if buffer is NULL  or length is unknown */
	if ((pSrcAddr == NULL) || (pDstAddr == NULL) || (dataLen == 0)) {
		/* Do not initiate transfer */
		return -1;
	}

	/* Ensure scatter and gather are transaction aligned */
	if (pConfig->srcGatherWidth % srcTrSize
	    || pConfig->dstScatterWidth % dstTrSize) {
		return -1;
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

	return descCount;
}