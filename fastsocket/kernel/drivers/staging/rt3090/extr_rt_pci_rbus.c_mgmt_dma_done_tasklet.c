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
struct TYPE_8__ {int MgmtDmaDone; } ;
struct TYPE_11__ {TYPE_1__ field; scalar_t__ word; } ;
struct TYPE_10__ {int /*<<< orphan*/  mgmt_dma_done_task; } ;
struct TYPE_9__ {int int_pending; int /*<<< orphan*/  irq_lock; scalar_t__ OS_Cookie; } ;
typedef  TYPE_2__* PRTMP_ADAPTER ;
typedef  TYPE_3__* POS_COOKIE ;
typedef  TYPE_4__ INT_SOURCE_CSR_STRUC ;

/* Variables and functions */
 int INT_MGMT_DLY ; 
 int /*<<< orphan*/  RTMPHandleMgmtRingDmaDoneInterrupt (TYPE_2__*) ; 
 int /*<<< orphan*/  RTMP_INT_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_INT_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ RTMP_TEST_FLAG (TYPE_2__*,int) ; 
 int fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int /*<<< orphan*/  rt2860_int_enable (TYPE_2__*,int) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void mgmt_dma_done_tasklet(unsigned long data)
{
	unsigned long flags;
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER) data;
    INT_SOURCE_CSR_STRUC	IntSource;
	POS_COOKIE pObj;

	// Do nothing if the driver is starting halt state.
	// This might happen when timer already been fired before cancel timer with mlmehalt
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST))
		return;

    pObj = (POS_COOKIE) pAd->OS_Cookie;

//	printk("mgmt_dma_done_process\n");
	IntSource.word = 0;
	IntSource.field.MgmtDmaDone = 1;
	pAd->int_pending &= ~INT_MGMT_DLY;

	RTMPHandleMgmtRingDmaDoneInterrupt(pAd);

	// if you use RTMP_SEM_LOCK, sometimes kernel will hang up, no any
	// bug report output
	RTMP_INT_LOCK(&pAd->irq_lock, flags);
	/*
	 * double check to avoid lose of interrupts
	 */
	if (pAd->int_pending & INT_MGMT_DLY)
	{
		tasklet_hi_schedule(&pObj->mgmt_dma_done_task);
		RTMP_INT_UNLOCK(&pAd->irq_lock, flags);
		return;
	}

	/* enable TxDataInt again */
	rt2860_int_enable(pAd, INT_MGMT_DLY);
	RTMP_INT_UNLOCK(&pAd->irq_lock, flags);
}