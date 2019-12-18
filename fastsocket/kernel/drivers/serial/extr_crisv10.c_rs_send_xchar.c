#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct tty_struct {scalar_t__ stopped; scalar_t__ driver_data; } ;
struct e100_serial {char x_char; int /*<<< orphan*/  line; int /*<<< orphan*/ * ocmdadr; scalar_t__ uses_dma_out; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,char) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 scalar_t__ IO_EXTRACT (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ IO_STATE_VALUE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R_DMA_CH6_CMD ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  e100_disable_txdma_channel (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_enable_serial_tx_ready_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  hold ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  rs_start (struct tty_struct*) ; 

__attribute__((used)) static void rs_send_xchar(struct tty_struct *tty, char ch)
{
	struct e100_serial *info = (struct e100_serial *)tty->driver_data;
	unsigned long flags;
	local_irq_save(flags);
	if (info->uses_dma_out) {
		/* Put the DMA on hold and disable the channel */
		*info->ocmdadr = IO_STATE(R_DMA_CH6_CMD, cmd, hold);
		while (IO_EXTRACT(R_DMA_CH6_CMD, cmd, *info->ocmdadr) !=
		       IO_STATE_VALUE(R_DMA_CH6_CMD, cmd, hold));
		e100_disable_txdma_channel(info);
	}

	/* Must make sure transmitter is not stopped before we can transmit */
	if (tty->stopped)
		rs_start(tty);

	/* Enable manual transmit interrupt and send from there */
	DFLOW(DEBUG_LOG(info->line, "rs_send_xchar 0x%02X\n", ch));
	info->x_char = ch;
	e100_enable_serial_tx_ready_irq(info);
	local_irq_restore(flags);
}