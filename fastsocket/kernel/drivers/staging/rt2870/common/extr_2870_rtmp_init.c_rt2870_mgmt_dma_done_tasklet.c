#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_3__* purbb_t ;
struct TYPE_13__ {int TxDmaIdx; scalar_t__ TxSwFreeIdx; TYPE_1__* Cell; } ;
struct TYPE_16__ {size_t bulkResetPipeid; TYPE_2__ MgmtRing; int /*<<< orphan*/  MLMEBulkOutLock; int /*<<< orphan*/ * BulkOutLock; void** BulkOutPending; } ;
struct TYPE_15__ {int SelfIdx; scalar_t__ BulkOutSize; void* bWaitingBulkOut; void* InUse; void* IRPPending; TYPE_5__* pAd; } ;
struct TYPE_14__ {scalar_t__ status; scalar_t__ context; } ;
struct TYPE_12__ {int /*<<< orphan*/ * pNdisPacket; } ;
typedef  TYPE_4__* PTX_CONTEXT ;
typedef  TYPE_5__* PRTMP_ADAPTER ;
typedef  int /*<<< orphan*/ * PNDIS_PACKET ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 size_t BULKOUT_MGMT_RESET_FLAG ; 
 int /*<<< orphan*/  CMDTHREAD_RESET_BULK_OUT ; 
 int /*<<< orphan*/  DBGPRINT_RAW (int /*<<< orphan*/ ,char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  INC_RING_INDEX (int,scalar_t__) ; 
 size_t MGMTPIPEIDX ; 
 scalar_t__ MGMT_RING_SIZE ; 
 int /*<<< orphan*/  RTMPFreeNdisPacket (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_IRQ_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_IRQ_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_SET_FLAG (TYPE_5__*,int) ; 
 scalar_t__ RTMP_TEST_FLAG (TYPE_5__*,int) ; 
 int /*<<< orphan*/  RTUSBEnqueueInternalCmd (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTUSBKickBulkOut (TYPE_5__*) ; 
 int /*<<< orphan*/  RTUSB_SET_BULK_FLAG (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 scalar_t__ USB_ST_NOERROR ; 
 int fRTMP_ADAPTER_BULKOUT_RESET ; 
 int fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int fRTMP_ADAPTER_RESET_IN_PROGRESS ; 
 int /*<<< orphan*/  fRTUSB_BULK_OUT_MLME ; 

__attribute__((used)) static void rt2870_mgmt_dma_done_tasklet(unsigned long data)
{
	PRTMP_ADAPTER 	pAd;
	PTX_CONTEXT		pMLMEContext;
	int				index;
	PNDIS_PACKET	pPacket;
	purbb_t			pUrb;
	NTSTATUS		Status;
	unsigned long	IrqFlags;


	pUrb			= (purbb_t)data;
	pMLMEContext	= (PTX_CONTEXT)pUrb->context;
	pAd 			= pMLMEContext->pAd;
	Status			= pUrb->status;
	index 			= pMLMEContext->SelfIdx;

	ASSERT((pAd->MgmtRing.TxDmaIdx == index));

	RTMP_IRQ_LOCK(&pAd->BulkOutLock[MGMTPIPEIDX], IrqFlags);


	if (Status != USB_ST_NOERROR)
	{
		//Bulk-Out fail status handle
		if ((!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET)))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("Bulk Out MLME Failed, Status=%d!\n", Status));
			// TODO: How to handle about the MLMEBulkOut failed issue. Need to resend the mgmt pkt?
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);
			pAd->bulkResetPipeid = (MGMTPIPEIDX | BULKOUT_MGMT_RESET_FLAG);
		}
	}

	pAd->BulkOutPending[MGMTPIPEIDX] = FALSE;
	RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[MGMTPIPEIDX], IrqFlags);

	RTMP_IRQ_LOCK(&pAd->MLMEBulkOutLock, IrqFlags);
	// Reset MLME context flags
	pMLMEContext->IRPPending = FALSE;
	pMLMEContext->InUse = FALSE;
	pMLMEContext->bWaitingBulkOut = FALSE;
	pMLMEContext->BulkOutSize = 0;

	pPacket = pAd->MgmtRing.Cell[index].pNdisPacket;
	pAd->MgmtRing.Cell[index].pNdisPacket = NULL;

	// Increase MgmtRing Index
	INC_RING_INDEX(pAd->MgmtRing.TxDmaIdx, MGMT_RING_SIZE);
	pAd->MgmtRing.TxSwFreeIdx++;
	RTMP_IRQ_UNLOCK(&pAd->MLMEBulkOutLock, IrqFlags);

	// No-matter success or fail, we free the mgmt packet.
	if (pPacket)
		RTMPFreeNdisPacket(pAd, pPacket);

	if ((RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS |
								fRTMP_ADAPTER_HALT_IN_PROGRESS |
								fRTMP_ADAPTER_NIC_NOT_EXIST))))
	{
		// do nothing and return directly.
	}
	else
	{
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET) &&
			((pAd->bulkResetPipeid & BULKOUT_MGMT_RESET_FLAG) == BULKOUT_MGMT_RESET_FLAG))
		{	// For Mgmt Bulk-Out failed, ignore it now.
			RTUSBEnqueueInternalCmd(pAd, CMDTHREAD_RESET_BULK_OUT, NULL, 0);
		}
		else
		{

			// Always call Bulk routine, even reset bulk.
			// The protectioon of rest bulk should be in BulkOut routine
			if (pAd->MgmtRing.TxSwFreeIdx < MGMT_RING_SIZE /* pMLMEContext->bWaitingBulkOut == TRUE */)
			{
				RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_MLME);
			}
				RTUSBKickBulkOut(pAd);
			}
		}

}