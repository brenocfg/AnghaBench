#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* purbb_t ;
struct TYPE_11__ {int bulkResetPipeid; int /*<<< orphan*/ * BulkOutLock; void** BulkOutPending; } ;
struct TYPE_10__ {size_t BulkOutPipeId; void* InUse; void* IRPPending; TYPE_3__* pAd; } ;
struct TYPE_9__ {scalar_t__ status; scalar_t__ context; } ;
typedef  TYPE_2__* PTX_CONTEXT ;
typedef  TYPE_3__* PRTMP_ADAPTER ;
typedef  scalar_t__ NTSTATUS ;

/* Variables and functions */
 int BULKOUT_MGMT_RESET_FLAG ; 
 int /*<<< orphan*/  CMDTHREAD_RESET_BULK_OUT ; 
 int /*<<< orphan*/  DBGPRINT_RAW (int /*<<< orphan*/ ,char*) ; 
 void* FALSE ; 
 int /*<<< orphan*/  MAX_TX_PROCESS ; 
 int MGMTPIPEIDX ; 
 int /*<<< orphan*/  NUM_OF_TX_RING ; 
 int /*<<< orphan*/  RTMPDeQueuePacket (TYPE_3__*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTMP_IRQ_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_IRQ_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_SEM_LOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_SEM_UNLOCK (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RTMP_SET_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTMP_TEST_FLAG (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTUSBEnqueueInternalCmd (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTUSBKickBulkOut (TYPE_3__*) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 scalar_t__ USB_ST_NOERROR ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_BULKOUT_RESET ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int /*<<< orphan*/  fRTMP_ADAPTER_RESET_IN_PROGRESS ; 

__attribute__((used)) static void rt2870_rts_frame_complete_tasklet(unsigned long data)
{
	PRTMP_ADAPTER	pAd;
	PTX_CONTEXT		pRTSContext;
	purbb_t			pUrb;
	NTSTATUS		Status;
	unsigned long	irqFlag;


	pUrb		= (purbb_t)data;
	pRTSContext	= (PTX_CONTEXT)pUrb->context;
	pAd			= pRTSContext->pAd;
	Status		= pUrb->status;

	// Reset RTS frame context flags
	RTMP_IRQ_LOCK(&pAd->BulkOutLock[0], irqFlag);
	pRTSContext->IRPPending = FALSE;
	pRTSContext->InUse		= FALSE;

	if (Status == USB_ST_NOERROR)
	{
		RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[0], irqFlag);
		RTMPDeQueuePacket(pAd, FALSE, NUM_OF_TX_RING, MAX_TX_PROCESS);
	}
	else	// STATUS_OTHER
	{
		if ((!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST)) &&
			(!RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET)))
		{
			DBGPRINT_RAW(RT_DEBUG_ERROR, ("Bulk Out RTS Frame Failed\n"));
			RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET);
			pAd->bulkResetPipeid = (MGMTPIPEIDX | BULKOUT_MGMT_RESET_FLAG);
			RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[0], irqFlag);
			RTUSBEnqueueInternalCmd(pAd, CMDTHREAD_RESET_BULK_OUT, NULL, 0);
		}
		else
		{
			RTMP_IRQ_UNLOCK(&pAd->BulkOutLock[0], irqFlag);
		}
	}

	RTMP_SEM_LOCK(&pAd->BulkOutLock[pRTSContext->BulkOutPipeId]);
	pAd->BulkOutPending[pRTSContext->BulkOutPipeId] = FALSE;
	RTMP_SEM_UNLOCK(&pAd->BulkOutLock[pRTSContext->BulkOutPipeId]);

	// Always call Bulk routine, even reset bulk.
	// The protectioon of rest bulk should be in BulkOut routine
	RTUSBKickBulkOut(pAd);

}