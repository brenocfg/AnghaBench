#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct etrax_recv_buffer {int dummy; } ;
struct etrax_dma_descr {scalar_t__ buf; } ;
struct TYPE_8__ {TYPE_3__* tty; } ;
struct TYPE_5__ {int /*<<< orphan*/ * buf; } ;
struct e100_serial {int* ioport; int tx_ctrl; int flags; TYPE_4__ port; TYPE_1__ xmit; int /*<<< orphan*/  irq; int /*<<< orphan*/  line; scalar_t__ tr_running; scalar_t__ uses_dma_out; void** ocmdadr; scalar_t__ uses_dma_in; void** icmdadr; struct etrax_dma_descr* rec_descr; } ;
struct TYPE_7__ {int /*<<< orphan*/  flags; TYPE_2__* termios; } ;
struct TYPE_6__ {int c_cflag; } ;

/* Variables and functions */
 int ASYNC_INITIALIZED ; 
 int /*<<< orphan*/  DEBUG_LOG (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DFLOW (int /*<<< orphan*/ ) ; 
 int HUPCL ; 
 void* IO_STATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t REG_TR_CTRL ; 
 int /*<<< orphan*/  R_DMA_CH6_CMD ; 
 int SERIAL_RECV_DESCRIPTORS ; 
 int /*<<< orphan*/  TTY_IO_ERROR ; 
 int /*<<< orphan*/  cmd ; 
 int /*<<< orphan*/  e100_disable_rx (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_disable_rxdma_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_disable_serial_data_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_disable_serial_tx_ready_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_disable_txdma_irq (struct e100_serial*) ; 
 int /*<<< orphan*/  e100_dtr (struct e100_serial*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  e100_rts (struct e100_serial*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_page (unsigned long) ; 
 int /*<<< orphan*/  kfree (struct etrax_recv_buffer*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct etrax_recv_buffer* phys_to_virt (scalar_t__) ; 
 int /*<<< orphan*/  printk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reset ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
shutdown(struct e100_serial * info)
{
	unsigned long flags;
	struct etrax_dma_descr *descr = info->rec_descr;
	struct etrax_recv_buffer *buffer;
	int i;

#ifndef CONFIG_SVINTO_SIM
	/* shut down the transmitter and receiver */
	DFLOW(DEBUG_LOG(info->line, "shutdown %i\n", info->line));
	e100_disable_rx(info);
	info->ioport[REG_TR_CTRL] = (info->tx_ctrl &= ~0x40);

	/* disable interrupts, reset dma channels */
	if (info->uses_dma_in) {
		e100_disable_rxdma_irq(info);
		*info->icmdadr = IO_STATE(R_DMA_CH6_CMD, cmd, reset);
		info->uses_dma_in = 0;
	} else {
		e100_disable_serial_data_irq(info);
	}

	if (info->uses_dma_out) {
		e100_disable_txdma_irq(info);
		info->tr_running = 0;
		*info->ocmdadr = IO_STATE(R_DMA_CH6_CMD, cmd, reset);
		info->uses_dma_out = 0;
	} else {
		e100_disable_serial_tx_ready_irq(info);
		info->tr_running = 0;
	}

#endif /* CONFIG_SVINTO_SIM */

	if (!(info->flags & ASYNC_INITIALIZED))
		return;

#ifdef SERIAL_DEBUG_OPEN
	printk("Shutting down serial port %d (irq %d)....\n", info->line,
	       info->irq);
#endif

	local_irq_save(flags);

	if (info->xmit.buf) {
		free_page((unsigned long)info->xmit.buf);
		info->xmit.buf = NULL;
	}

	for (i = 0; i < SERIAL_RECV_DESCRIPTORS; i++)
		if (descr[i].buf) {
			buffer = phys_to_virt(descr[i].buf) - sizeof *buffer;
			kfree(buffer);
			descr[i].buf = 0;
		}

	if (!info->port.tty || (info->port.tty->termios->c_cflag & HUPCL)) {
		/* hang up DTR and RTS if HUPCL is enabled */
		e100_dtr(info, 0);
		e100_rts(info, 0); /* could check CRTSCTS before doing this */
	}

	if (info->port.tty)
		set_bit(TTY_IO_ERROR, &info->port.tty->flags);

	info->flags &= ~ASYNC_INITIALIZED;
	local_irq_restore(flags);
}