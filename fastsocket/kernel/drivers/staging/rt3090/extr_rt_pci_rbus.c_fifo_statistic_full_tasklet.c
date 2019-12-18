#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  fifo_statistic_full_task; } ;
struct TYPE_6__ {int int_pending; int /*<<< orphan*/  irq_lock; scalar_t__ OS_Cookie; } ;
typedef  TYPE_1__* PRTMP_ADAPTER ;
typedef  TYPE_2__* POS_COOKIE ;

/* Variables and functions */
 int FifoStaFullInt ; 
 int /*<<< orphan*/  NICUpdateFifoStaCounters (TYPE_1__*) ; 
 int /*<<< orphan*/  RTMP_INT_LOCK (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  RTMP_INT_UNLOCK (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ RTMP_TEST_FLAG (TYPE_1__*,int) ; 
 int fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int /*<<< orphan*/  rt2860_int_enable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

void fifo_statistic_full_tasklet(unsigned long data)
{
	unsigned long flags;
	PRTMP_ADAPTER pAd = (PRTMP_ADAPTER) data;
	POS_COOKIE pObj;

	// Do nothing if the driver is starting halt state.
	// This might happen when timer already been fired before cancel timer with mlmehalt
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS | fRTMP_ADAPTER_NIC_NOT_EXIST))
		return;

    pObj = (POS_COOKIE) pAd->OS_Cookie;

	pAd->int_pending &= ~(FifoStaFullInt);
	NICUpdateFifoStaCounters(pAd);

	RTMP_INT_LOCK(&pAd->irq_lock, flags);
	/*
	 * double check to avoid rotting packet
	 */
	if (pAd->int_pending & FifoStaFullInt)
	{
		tasklet_hi_schedule(&pObj->fifo_statistic_full_task);
		RTMP_INT_UNLOCK(&pAd->irq_lock, flags);
		return;
	}

	/* enable RxINT again */

	rt2860_int_enable(pAd, FifoStaFullInt);
	RTMP_INT_UNLOCK(&pAd->irq_lock, flags);

}