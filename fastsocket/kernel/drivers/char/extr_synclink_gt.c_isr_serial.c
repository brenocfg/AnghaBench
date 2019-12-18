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
struct TYPE_6__ {int /*<<< orphan*/  exithunt; int /*<<< orphan*/  rxidle; int /*<<< orphan*/  brk; } ;
struct TYPE_5__ {int flags; scalar_t__ tty; } ;
struct TYPE_4__ {scalar_t__ mode; } ;
struct slgt_info {int irq_occurred; unsigned short ignore_status_mask; int read_status_mask; int /*<<< orphan*/  event_wait_q; TYPE_3__ icount; scalar_t__ rx_pio; TYPE_2__ port; scalar_t__ tx_count; TYPE_1__ params; int /*<<< orphan*/  device_name; } ;

/* Variables and functions */
 int ASYNC_SAK ; 
 int /*<<< orphan*/  DBGISR (char*) ; 
 unsigned short IRQ_CTS ; 
 unsigned short IRQ_DCD ; 
 unsigned short IRQ_DSR ; 
 unsigned short IRQ_RI ; 
 unsigned short IRQ_RXBREAK ; 
 unsigned short IRQ_RXDATA ; 
 unsigned short IRQ_RXIDLE ; 
 unsigned short IRQ_RXOVER ; 
 unsigned short IRQ_TXIDLE ; 
 unsigned short IRQ_TXUNDER ; 
 int MASK_BREAK ; 
 scalar_t__ MGSL_MODE_ASYNC ; 
 unsigned short RXBREAK ; 
 unsigned short RXIDLE ; 
 int /*<<< orphan*/  SSR ; 
 int /*<<< orphan*/  TTY_BREAK ; 
 int /*<<< orphan*/  cts_change (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  dcd_change (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  do_SAK (scalar_t__) ; 
 int /*<<< orphan*/  dsr_change (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  isr_rxdata (struct slgt_info*) ; 
 int /*<<< orphan*/  isr_txeom (struct slgt_info*,unsigned short) ; 
 unsigned short rd_reg16 (struct slgt_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ri_change (struct slgt_info*,unsigned short) ; 
 int /*<<< orphan*/  rx_start (struct slgt_info*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wr_reg16 (struct slgt_info*,int /*<<< orphan*/ ,unsigned short) ; 

__attribute__((used)) static void isr_serial(struct slgt_info *info)
{
	unsigned short status = rd_reg16(info, SSR);

	DBGISR(("%s isr_serial status=%04X\n", info->device_name, status));

	wr_reg16(info, SSR, status); /* clear pending */

	info->irq_occurred = true;

	if (info->params.mode == MGSL_MODE_ASYNC) {
		if (status & IRQ_TXIDLE) {
			if (info->tx_count)
				isr_txeom(info, status);
		}
		if (info->rx_pio && (status & IRQ_RXDATA))
			isr_rxdata(info);
		if ((status & IRQ_RXBREAK) && (status & RXBREAK)) {
			info->icount.brk++;
			/* process break detection if tty control allows */
			if (info->port.tty) {
				if (!(status & info->ignore_status_mask)) {
					if (info->read_status_mask & MASK_BREAK) {
						tty_insert_flip_char(info->port.tty, 0, TTY_BREAK);
						if (info->port.flags & ASYNC_SAK)
							do_SAK(info->port.tty);
					}
				}
			}
		}
	} else {
		if (status & (IRQ_TXIDLE + IRQ_TXUNDER))
			isr_txeom(info, status);
		if (info->rx_pio && (status & IRQ_RXDATA))
			isr_rxdata(info);
		if (status & IRQ_RXIDLE) {
			if (status & RXIDLE)
				info->icount.rxidle++;
			else
				info->icount.exithunt++;
			wake_up_interruptible(&info->event_wait_q);
		}

		if (status & IRQ_RXOVER)
			rx_start(info);
	}

	if (status & IRQ_DSR)
		dsr_change(info, status);
	if (status & IRQ_CTS)
		cts_change(info, status);
	if (status & IRQ_DCD)
		dcd_change(info, status);
	if (status & IRQ_RI)
		ri_change(info, status);
}