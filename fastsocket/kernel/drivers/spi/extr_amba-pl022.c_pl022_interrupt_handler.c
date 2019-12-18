#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
typedef  int u16 ;
struct spi_message {int /*<<< orphan*/  state; int /*<<< orphan*/  actual_length; } ;
struct pl022 {scalar_t__ tx; scalar_t__ tx_end; scalar_t__ rx; scalar_t__ rx_end; int /*<<< orphan*/  pump_transfers; TYPE_3__* cur_chip; TYPE_2__* cur_transfer; TYPE_1__* adev; int /*<<< orphan*/  virtbase; struct spi_message* cur_msg; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* cs_control ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {scalar_t__ cs_change; scalar_t__ len; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int CLEAR_ALL_INTERRUPTS ; 
 int DISABLE_ALL_INTERRUPTS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  SSP_CHIP_DESELECT ; 
 int /*<<< orphan*/  SSP_CR1 (int /*<<< orphan*/ ) ; 
 int SSP_CR1_MASK_SSE ; 
 int /*<<< orphan*/  SSP_ICR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSP_IMSC (int /*<<< orphan*/ ) ; 
 int SSP_IMSC_MASK_TXIM ; 
 int /*<<< orphan*/  SSP_MIS (int /*<<< orphan*/ ) ; 
 int SSP_MIS_MASK_RORMIS ; 
 int /*<<< orphan*/  SSP_SR (int /*<<< orphan*/ ) ; 
 int SSP_SR_MASK_RFF ; 
 int SSP_SR_MASK_TNF ; 
 int /*<<< orphan*/  STATE_ERROR ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  next_transfer (struct pl022*) ; 
 int readw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  readwriter (struct pl022*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t pl022_interrupt_handler(int irq, void *dev_id)
{
	struct pl022 *pl022 = dev_id;
	struct spi_message *msg = pl022->cur_msg;
	u16 irq_status = 0;
	u16 flag = 0;

	if (unlikely(!msg)) {
		dev_err(&pl022->adev->dev,
			"bad message state in interrupt handler");
		/* Never fail */
		return IRQ_HANDLED;
	}

	/* Read the Interrupt Status Register */
	irq_status = readw(SSP_MIS(pl022->virtbase));

	if (unlikely(!irq_status))
		return IRQ_NONE;

	/* This handles the error code interrupts */
	if (unlikely(irq_status & SSP_MIS_MASK_RORMIS)) {
		/*
		 * Overrun interrupt - bail out since our Data has been
		 * corrupted
		 */
		dev_err(&pl022->adev->dev,
			"FIFO overrun\n");
		if (readw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_RFF)
			dev_err(&pl022->adev->dev,
				"RXFIFO is full\n");
		if (readw(SSP_SR(pl022->virtbase)) & SSP_SR_MASK_TNF)
			dev_err(&pl022->adev->dev,
				"TXFIFO is full\n");

		/*
		 * Disable and clear interrupts, disable SSP,
		 * mark message with bad status so it can be
		 * retried.
		 */
		writew(DISABLE_ALL_INTERRUPTS,
		       SSP_IMSC(pl022->virtbase));
		writew(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
		writew((readw(SSP_CR1(pl022->virtbase)) &
			(~SSP_CR1_MASK_SSE)), SSP_CR1(pl022->virtbase));
		msg->state = STATE_ERROR;

		/* Schedule message queue handler */
		tasklet_schedule(&pl022->pump_transfers);
		return IRQ_HANDLED;
	}

	readwriter(pl022);

	if ((pl022->tx == pl022->tx_end) && (flag == 0)) {
		flag = 1;
		/* Disable Transmit interrupt */
		writew(readw(SSP_IMSC(pl022->virtbase)) &
		       (~SSP_IMSC_MASK_TXIM),
		       SSP_IMSC(pl022->virtbase));
	}

	/*
	 * Since all transactions must write as much as shall be read,
	 * we can conclude the entire transaction once RX is complete.
	 * At this point, all TX will always be finished.
	 */
	if (pl022->rx >= pl022->rx_end) {
		writew(DISABLE_ALL_INTERRUPTS,
		       SSP_IMSC(pl022->virtbase));
		writew(CLEAR_ALL_INTERRUPTS, SSP_ICR(pl022->virtbase));
		if (unlikely(pl022->rx > pl022->rx_end)) {
			dev_warn(&pl022->adev->dev, "read %u surplus "
				 "bytes (did you request an odd "
				 "number of bytes on a 16bit bus?)\n",
				 (u32) (pl022->rx - pl022->rx_end));
		}
		/* Update total bytes transfered */
		msg->actual_length += pl022->cur_transfer->len;
		if (pl022->cur_transfer->cs_change)
			pl022->cur_chip->
				cs_control(SSP_CHIP_DESELECT);
		/* Move to next transfer */
		msg->state = next_transfer(pl022);
		tasklet_schedule(&pl022->pump_transfers);
		return IRQ_HANDLED;
	}

	return IRQ_HANDLED;
}