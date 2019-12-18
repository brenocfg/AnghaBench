#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* purbb_t ;
typedef  size_t UCHAR ;
struct TYPE_13__ {scalar_t__ bCurWriting; TYPE_3__* pAd; } ;
struct TYPE_12__ {scalar_t__* DeQueueRunning; TYPE_1__* TxSwQueue; TYPE_4__* TxContext; } ;
struct TYPE_11__ {scalar_t__ context; } ;
struct TYPE_10__ {scalar_t__ Number; } ;
typedef  TYPE_3__* PRTMP_ADAPTER ;
typedef  TYPE_4__* PHT_TX_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  CMDTHREAD_RESET_BULK_OUT ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  MAX_TX_PROCESS ; 
 int /*<<< orphan*/  RTMPDeQueuePacket (TYPE_3__*,scalar_t__,size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ RTMP_TEST_FLAG (TYPE_3__*,int) ; 
 int /*<<< orphan*/  RTUSBEnqueueInternalCmd (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTUSBKickBulkOut (TYPE_3__*) ; 
 int /*<<< orphan*/  RTUSB_SET_BULK_FLAG (TYPE_3__*,int) ; 
 int fRTMP_ADAPTER_BULKOUT_RESET ; 
 int fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int fRTMP_ADAPTER_RESET_IN_PROGRESS ; 
 int fRTUSB_BULK_OUT_DATA_NORMAL ; 
 int /*<<< orphan*/  rt2870_dataout_complete_tasklet (unsigned long) ; 

__attribute__((used)) static void rt2870_ac1_dma_done_tasklet(unsigned long data)
{
	PRTMP_ADAPTER		pAd;
	PHT_TX_CONTEXT		pHTTXContext;
	UCHAR				BulkOutPipeId = 1;
	purbb_t				pUrb;


	pUrb			= (purbb_t)data;
	pHTTXContext	= (PHT_TX_CONTEXT)pUrb->context;
	pAd				= pHTTXContext->pAd;

	rt2870_dataout_complete_tasklet((unsigned long)pUrb);

	if ((RTMP_TEST_FLAG(pAd, (fRTMP_ADAPTER_RESET_IN_PROGRESS |
								fRTMP_ADAPTER_HALT_IN_PROGRESS |
								fRTMP_ADAPTER_NIC_NOT_EXIST))))
	{
		// do nothing and return directly.
	}
	else
	{
		if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_BULKOUT_RESET))
		{
			RTUSBEnqueueInternalCmd(pAd, CMDTHREAD_RESET_BULK_OUT, NULL, 0);
		}
		else
		{	pHTTXContext = &pAd->TxContext[BulkOutPipeId];
			if ((pAd->TxSwQueue[BulkOutPipeId].Number > 0) &&
				/*((pHTTXContext->CurWritePosition > (pHTTXContext->NextBulkOutPosition + 0x6000)) || (pHTTXContext->NextBulkOutPosition > pHTTXContext->CurWritePosition + 0x6000)) && */
				(pAd->DeQueueRunning[BulkOutPipeId] == FALSE) &&
				(pHTTXContext->bCurWriting == FALSE))
			{
				RTMPDeQueuePacket(pAd, FALSE, BulkOutPipeId, MAX_TX_PROCESS);
			}

			RTUSB_SET_BULK_FLAG(pAd, fRTUSB_BULK_OUT_DATA_NORMAL<<1);
			RTUSBKickBulkOut(pAd);
		}
	}


	return;
}