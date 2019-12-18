#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct pt_regs {int dummy; } ;
typedef  TYPE_1__* purbb_t ;
typedef  int /*<<< orphan*/  VOID ;
typedef  int UCHAR ;
struct TYPE_11__ {unsigned long data; } ;
struct TYPE_10__ {int BulkOutPipeId; TYPE_2__* pAd; } ;
struct TYPE_9__ {TYPE_5__ hcca_dma_done_task; TYPE_5__ ac3_dma_done_task; TYPE_5__ ac2_dma_done_task; TYPE_5__ ac1_dma_done_task; TYPE_5__ ac0_dma_done_task; } ;
struct TYPE_8__ {int /*<<< orphan*/  BulkOutDataOneSecCount; scalar_t__ OS_Cookie; } ;
struct TYPE_7__ {scalar_t__ context; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;
typedef  TYPE_3__* POS_COOKIE ;
typedef  TYPE_4__* PHT_TX_CONTEXT ;

/* Variables and functions */
 int /*<<< orphan*/  tasklet_hi_schedule (TYPE_5__*) ; 

VOID RTUSBBulkOutDataPacketComplete(purbb_t pUrb, struct pt_regs *pt_regs)
{
	PHT_TX_CONTEXT	pHTTXContext;
	PRTMP_ADAPTER	pAd;
	POS_COOKIE 		pObj;
	UCHAR			BulkOutPipeId;


	pHTTXContext	= (PHT_TX_CONTEXT)pUrb->context;
	pAd 			= pHTTXContext->pAd;
	pObj 			= (POS_COOKIE) pAd->OS_Cookie;

	// Store BulkOut PipeId
	BulkOutPipeId	= pHTTXContext->BulkOutPipeId;
	pAd->BulkOutDataOneSecCount++;

	switch (BulkOutPipeId)
	{
		case 0:
				pObj->ac0_dma_done_task.data = (unsigned long)pUrb;
				tasklet_hi_schedule(&pObj->ac0_dma_done_task);
				break;
		case 1:
				pObj->ac1_dma_done_task.data = (unsigned long)pUrb;
				tasklet_hi_schedule(&pObj->ac1_dma_done_task);
				break;
		case 2:
				pObj->ac2_dma_done_task.data = (unsigned long)pUrb;
				tasklet_hi_schedule(&pObj->ac2_dma_done_task);
				break;
		case 3:
				pObj->ac3_dma_done_task.data = (unsigned long)pUrb;
				tasklet_hi_schedule(&pObj->ac3_dma_done_task);
				break;
		case 4:
				pObj->hcca_dma_done_task.data = (unsigned long)pUrb;
				tasklet_hi_schedule(&pObj->hcca_dma_done_task);
				break;
	}
}