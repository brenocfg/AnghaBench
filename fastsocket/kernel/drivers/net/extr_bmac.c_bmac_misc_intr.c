#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  collisions; int /*<<< orphan*/  tx_fifo_errors; int /*<<< orphan*/  tx_errors; int /*<<< orphan*/  rx_frame_errors; int /*<<< orphan*/  rx_over_errors; int /*<<< orphan*/  rx_length_errors; int /*<<< orphan*/  rx_crc_errors; int /*<<< orphan*/  rx_errors; } ;
struct net_device {TYPE_1__ stats; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 unsigned int RxAlignCntExp ; 
 unsigned int RxCRCCntExp ; 
 unsigned int RxErrorMask ; 
 unsigned int RxLenCntExp ; 
 unsigned int RxOverFlow ; 
 int /*<<< orphan*/  STATUS ; 
 unsigned int TxErrorMask ; 
 unsigned int TxNormalCollExp ; 
 unsigned int TxUnderrun ; 
 int /*<<< orphan*/  XXDEBUG (char*) ; 
 unsigned int bmread (struct net_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  miscintcount ; 

__attribute__((used)) static irqreturn_t bmac_misc_intr(int irq, void *dev_id)
{
	struct net_device *dev = (struct net_device *) dev_id;
	unsigned int status = bmread(dev, STATUS);
	if (miscintcount++ < 10) {
		XXDEBUG(("bmac_misc_intr\n"));
	}
	/* XXDEBUG(("bmac_misc_intr, status=%#08x\n", status)); */
	/*     bmac_txdma_intr_inner(irq, dev_id); */
	/*   if (status & FrameReceived) dev->stats.rx_dropped++; */
	if (status & RxErrorMask) dev->stats.rx_errors++;
	if (status & RxCRCCntExp) dev->stats.rx_crc_errors++;
	if (status & RxLenCntExp) dev->stats.rx_length_errors++;
	if (status & RxOverFlow) dev->stats.rx_over_errors++;
	if (status & RxAlignCntExp) dev->stats.rx_frame_errors++;

	/*   if (status & FrameSent) dev->stats.tx_dropped++; */
	if (status & TxErrorMask) dev->stats.tx_errors++;
	if (status & TxUnderrun) dev->stats.tx_fifo_errors++;
	if (status & TxNormalCollExp) dev->stats.collisions++;
	return IRQ_HANDLED;
}