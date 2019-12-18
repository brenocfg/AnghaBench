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
typedef  size_t uint32_t ;
typedef  int /*<<< orphan*/  dmacHw_HANDLE_t ;
struct TYPE_10__ {TYPE_2__* pTail; TYPE_2__* pHead; } ;
typedef  TYPE_3__ dmacHw_DESC_RING_t ;
struct TYPE_11__ {scalar_t__ transferMode; } ;
typedef  TYPE_4__ dmacHw_CONFIG_t ;
struct TYPE_8__ {int hi; int lo; } ;
struct TYPE_9__ {size_t sstat; TYPE_1__ ctl; scalar_t__ dar; } ;

/* Variables and functions */
 scalar_t__ DmaIsFlowController (void*) ; 
 int /*<<< orphan*/  dmacHw_ASSERT (int /*<<< orphan*/ ) ; 
 int dmacHw_DESC_FREE ; 
 TYPE_3__* dmacHw_GET_DESC_RING (void*) ; 
 int /*<<< orphan*/  dmacHw_NEXT_DESC (TYPE_3__*,int /*<<< orphan*/ ) ; 
 size_t dmacHw_REG_CTL_BLOCK_TS_MASK ; 
#define  dmacHw_REG_CTL_SRC_TR_WIDTH_16 131 
#define  dmacHw_REG_CTL_SRC_TR_WIDTH_32 130 
#define  dmacHw_REG_CTL_SRC_TR_WIDTH_64 129 
#define  dmacHw_REG_CTL_SRC_TR_WIDTH_8 128 
 int dmacHw_REG_CTL_SRC_TR_WIDTH_MASK ; 
 scalar_t__ dmacHw_TRANSFER_MODE_CONTINUOUS ; 
 int /*<<< orphan*/  pTail ; 

int dmacHw_readTransferredData(dmacHw_HANDLE_t handle,	/*  [ IN ] DMA Channel handle */
			       dmacHw_CONFIG_t *pConfig,	/*   [ IN ]  Configuration settings */
			       void *pDescriptor,	/*   [ IN ] Descriptor buffer */
			       void **ppBbuf,	/*   [ OUT ] Data received */
			       size_t *pLlen	/*   [ OUT ] Length of the data received */
    ) {
	dmacHw_DESC_RING_t *pRing = dmacHw_GET_DESC_RING(pDescriptor);

	(void)handle;

	if (pConfig->transferMode != dmacHw_TRANSFER_MODE_CONTINUOUS) {
		if (((pRing->pTail->ctl.hi & dmacHw_DESC_FREE) == 0) ||
		    (pRing->pTail == pRing->pHead)
		    ) {
			/* No receive data available */
			*ppBbuf = (char *)NULL;
			*pLlen = 0;

			return 0;
		}
	}

	/* Return read buffer and length */
	*ppBbuf = (char *)pRing->pTail->dar;

	/* Extract length of the received data */
	if (DmaIsFlowController(pDescriptor)) {
		uint32_t srcTrSize = 0;

		switch (pRing->pTail->ctl.lo & dmacHw_REG_CTL_SRC_TR_WIDTH_MASK) {
		case dmacHw_REG_CTL_SRC_TR_WIDTH_8:
			srcTrSize = 1;
			break;
		case dmacHw_REG_CTL_SRC_TR_WIDTH_16:
			srcTrSize = 2;
			break;
		case dmacHw_REG_CTL_SRC_TR_WIDTH_32:
			srcTrSize = 4;
			break;
		case dmacHw_REG_CTL_SRC_TR_WIDTH_64:
			srcTrSize = 8;
			break;
		default:
			dmacHw_ASSERT(0);
		}
		/* Calculate length from the block size */
		*pLlen =
		    (pRing->pTail->ctl.hi & dmacHw_REG_CTL_BLOCK_TS_MASK) *
		    srcTrSize;
	} else {
		/* Extract length from the source peripheral */
		*pLlen = pRing->pTail->sstat;
	}

	/* Advance tail to next descriptor */
	dmacHw_NEXT_DESC(pRing, pTail);

	return 1;
}