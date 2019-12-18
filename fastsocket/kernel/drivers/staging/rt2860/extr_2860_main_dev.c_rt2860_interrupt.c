#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct net_device {TYPE_1__* ml_priv; } ;
struct TYPE_16__ {int word; } ;
struct TYPE_15__ {int /*<<< orphan*/  ac0_dma_done_task; int /*<<< orphan*/  ac1_dma_done_task; int /*<<< orphan*/  ac2_dma_done_task; int /*<<< orphan*/  ac3_dma_done_task; int /*<<< orphan*/  hcca_dma_done_task; int /*<<< orphan*/  rx_done_task; int /*<<< orphan*/  mgmt_dma_done_task; int /*<<< orphan*/  fifo_statistic_full_task; } ;
struct TYPE_14__ {int int_disable_mask; int int_pending; int /*<<< orphan*/  bPCIclkOff; scalar_t__ OS_Cookie; } ;
typedef  TYPE_1__* PRTMP_ADAPTER ;
typedef  TYPE_2__* POS_COOKIE ;
typedef  int /*<<< orphan*/  IRQ_HANDLE_TYPE ;
typedef  TYPE_3__ INT_SOURCE_CSR_STRUC ;
typedef  int /*<<< orphan*/  BOOLEAN ;

/* Variables and functions */
 int AutoWakeupInt ; 
 int /*<<< orphan*/  DBGPRINT (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  FALSE ; 
 int FifoStaFullInt ; 
 int INT_AC0_DLY ; 
 int INT_AC1_DLY ; 
 int INT_AC2_DLY ; 
 int INT_AC3_DLY ; 
 int INT_HCCA_DLY ; 
 int INT_MGMT_DLY ; 
 int INT_RX ; 
 int /*<<< orphan*/  INT_SOURCE_CSR ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  NICUpdateFifoStaCounters (TYPE_1__*) ; 
 int PreTBTTInt ; 
 int /*<<< orphan*/  RTMPHandlePreTBTTInterrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  RTMPHandleRxCoherentInterrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  RTMPHandleTBTTInterrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  RTMPHandleTwakeupInterrupt (TYPE_1__*) ; 
 int /*<<< orphan*/  RTMP_IO_READ32 (TYPE_1__*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  RTMP_IO_WRITE32 (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  RTMP_SET_FLAG (TYPE_1__*,int) ; 
 scalar_t__ RTMP_TEST_FLAG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  RT_DEBUG_ERROR ; 
 int RxCoherent ; 
 int TBTTInt ; 
 int TxCoherent ; 
 int fRTMP_ADAPTER_HALT_IN_PROGRESS ; 
 int fRTMP_ADAPTER_NIC_NOT_EXIST ; 
 int fRTMP_ADAPTER_RESET_IN_PROGRESS ; 
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rt2860_int_disable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  tasklet_hi_schedule (int /*<<< orphan*/ *) ; 

IRQ_HANDLE_TYPE
rt2860_interrupt(int irq, void *dev_instance)
{
	struct net_device *net_dev = (struct net_device *) dev_instance;
	PRTMP_ADAPTER pAd = net_dev->ml_priv;
	INT_SOURCE_CSR_STRUC	IntSource;
	POS_COOKIE pObj;
	BOOLEAN	bOldValue;

	pObj = (POS_COOKIE) pAd->OS_Cookie;


	/* Note 03312008: we can not return here before
		RTMP_IO_READ32(pAd, INT_SOURCE_CSR, &IntSource.word);
		RTMP_IO_WRITE32(pAd, INT_SOURCE_CSR, IntSource.word);
		Or kernel will panic after ifconfig ra0 down sometimes */


	//
	// Inital the Interrupt source.
	//
	IntSource.word = 0x00000000L;
//	McuIntSource.word = 0x00000000L;

	//
	// Get the interrupt sources & saved to local variable
	//
	//RTMP_IO_READ32(pAd, where, &McuIntSource.word);
	//RTMP_IO_WRITE32(pAd, , McuIntSource.word);

	//
	// Flag fOP_STATUS_DOZE On, means ASIC put to sleep, elase means ASICK WakeUp
	// And at the same time, clock maybe turned off that say there is no DMA service.
	// when ASIC get to sleep.
	// To prevent system hang on power saving.
	// We need to check it before handle the INT_SOURCE_CSR, ASIC must be wake up.
	//
	// RT2661 => when ASIC is sleeping, MAC register cannot be read and written.
	// RT2860 => when ASIC is sleeping, MAC register can be read and written.

	bOldValue = pAd->bPCIclkOff;
	pAd->bPCIclkOff = FALSE;
	{
		RTMP_IO_READ32(pAd, INT_SOURCE_CSR, &IntSource.word);
		RTMP_IO_WRITE32(pAd, INT_SOURCE_CSR, IntSource.word); // write 1 to clear
	}
	pAd->bPCIclkOff = bOldValue;

	// Do nothing if Reset in progress
	if (RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_RESET_IN_PROGRESS) ||
		RTMP_TEST_FLAG(pAd, fRTMP_ADAPTER_HALT_IN_PROGRESS))
	{
		return IRQ_HANDLED;
	}

	//
	// Handle interrupt, walk through all bits
	// Should start from highest priority interrupt
	// The priority can be adjust by altering processing if statement
	//

	// If required spinlock, each interrupt service routine has to acquire
	// and release itself.
	//

	// Do nothing if NIC doesn't exist
	if (IntSource.word == 0xffffffff)
	{
		RTMP_SET_FLAG(pAd, fRTMP_ADAPTER_NIC_NOT_EXIST | fRTMP_ADAPTER_HALT_IN_PROGRESS);
		printk("snowpin - IntSource.word == 0xffffffff\n");
		return IRQ_HANDLED;
	}

	if (IntSource.word & TxCoherent)
	{
		DBGPRINT(RT_DEBUG_ERROR, (">>>TxCoherent<<<\n"));
		RTMPHandleRxCoherentInterrupt(pAd);
	}

	if (IntSource.word & RxCoherent)
	{
		DBGPRINT(RT_DEBUG_ERROR, (">>>RxCoherent<<<\n"));
		RTMPHandleRxCoherentInterrupt(pAd);
	}

	if (IntSource.word & FifoStaFullInt)
	{
#if 1
		if ((pAd->int_disable_mask & FifoStaFullInt) == 0)
		{
			/* mask FifoStaFullInt */
			rt2860_int_disable(pAd, FifoStaFullInt);
			tasklet_hi_schedule(&pObj->fifo_statistic_full_task);
		}
		pAd->int_pending |= FifoStaFullInt;
#else
		NICUpdateFifoStaCounters(pAd);
#endif
	}

	if (IntSource.word & INT_MGMT_DLY)
	{
		if ((pAd->int_disable_mask & INT_MGMT_DLY) ==0 )
		{
			rt2860_int_disable(pAd, INT_MGMT_DLY);
			tasklet_hi_schedule(&pObj->mgmt_dma_done_task);
		}
		pAd->int_pending |= INT_MGMT_DLY ;
	}

	if (IntSource.word & INT_RX)
	{
		if ((pAd->int_disable_mask & INT_RX) == 0)
		{
			/* mask RxINT */
			rt2860_int_disable(pAd, INT_RX);
			tasklet_hi_schedule(&pObj->rx_done_task);
		}
		pAd->int_pending |= INT_RX;
	}

	if (IntSource.word & INT_HCCA_DLY)
	{

		if ((pAd->int_disable_mask & INT_HCCA_DLY) == 0)
		{
			/* mask TxDataInt */
			rt2860_int_disable(pAd, INT_HCCA_DLY);
			tasklet_hi_schedule(&pObj->hcca_dma_done_task);
		}
		pAd->int_pending |= INT_HCCA_DLY;
	}

	if (IntSource.word & INT_AC3_DLY)
	{

		if ((pAd->int_disable_mask & INT_AC3_DLY) == 0)
		{
			/* mask TxDataInt */
			rt2860_int_disable(pAd, INT_AC3_DLY);
			tasklet_hi_schedule(&pObj->ac3_dma_done_task);
		}
		pAd->int_pending |= INT_AC3_DLY;
	}

	if (IntSource.word & INT_AC2_DLY)
	{

		if ((pAd->int_disable_mask & INT_AC2_DLY) == 0)
		{
			/* mask TxDataInt */
			rt2860_int_disable(pAd, INT_AC2_DLY);
			tasklet_hi_schedule(&pObj->ac2_dma_done_task);
		}
		pAd->int_pending |= INT_AC2_DLY;
	}

	if (IntSource.word & INT_AC1_DLY)
	{

		pAd->int_pending |= INT_AC1_DLY;

		if ((pAd->int_disable_mask & INT_AC1_DLY) == 0)
		{
			/* mask TxDataInt */
			rt2860_int_disable(pAd, INT_AC1_DLY);
			tasklet_hi_schedule(&pObj->ac1_dma_done_task);
		}

	}

	if (IntSource.word & INT_AC0_DLY)
	{
		pAd->int_pending |= INT_AC0_DLY;

		if ((pAd->int_disable_mask & INT_AC0_DLY) == 0)
		{
			/* mask TxDataInt */
			rt2860_int_disable(pAd, INT_AC0_DLY);
			tasklet_hi_schedule(&pObj->ac0_dma_done_task);
		}

	}

    if (IntSource.word & PreTBTTInt)
	{
		RTMPHandlePreTBTTInterrupt(pAd);
	}

	if (IntSource.word & TBTTInt)
	{
		RTMPHandleTBTTInterrupt(pAd);
	}

	if (IntSource.word & AutoWakeupInt)
		RTMPHandleTwakeupInterrupt(pAd);

    return  IRQ_HANDLED;
}