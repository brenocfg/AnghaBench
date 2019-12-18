#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  scalar_t__ u32 ;
typedef  int u16 ;
struct jsm_channel {size_t ch_w_tail; size_t ch_w_head; int ch_flags; int ch_cached_lsr; int ch_t_tlevel; int /*<<< orphan*/  uart_port; scalar_t__ ch_txcount; int /*<<< orphan*/ * ch_wqueue; TYPE_2__* ch_neo_uart; TYPE_1__* ch_bd; } ;
struct TYPE_4__ {int /*<<< orphan*/  txrxburst; int /*<<< orphan*/  txrx; int /*<<< orphan*/  lsr; } ;
struct TYPE_3__ {int /*<<< orphan*/  pci_dev; } ;

/* Variables and functions */
 int CH_BREAK_SENDING ; 
 int CH_FIFO_ENABLED ; 
 int CH_STOP ; 
 int CH_TX_FIFO_EMPTY ; 
 int CH_TX_FIFO_LWM ; 
 int /*<<< orphan*/  INFO ; 
 int UART_17158_TX_FIFOSIZE ; 
 int UART_LSR_THRE ; 
 int WQUEUEMASK ; 
 int WQUEUESIZE ; 
 int /*<<< orphan*/  WRITE ; 
 int /*<<< orphan*/  jsm_printk (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jsm_tty_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy_toio (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int min (int,int) ; 
 int readb (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uart_write_wakeup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writeb (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void neo_copy_data_from_queue_to_uart(struct jsm_channel *ch)
{
	u16 head;
	u16 tail;
	int n;
	int s;
	int qlen;
	u32 len_written = 0;

	if (!ch)
		return;

	/* No data to write to the UART */
	if (ch->ch_w_tail == ch->ch_w_head)
		return;

	/* If port is "stopped", don't send any data to the UART */
	if ((ch->ch_flags & CH_STOP) || (ch->ch_flags & CH_BREAK_SENDING))
		return;
	/*
	 * If FIFOs are disabled. Send data directly to txrx register
	 */
	if (!(ch->ch_flags & CH_FIFO_ENABLED)) {
		u8 lsrbits = readb(&ch->ch_neo_uart->lsr);

		ch->ch_cached_lsr |= lsrbits;
		if (ch->ch_cached_lsr & UART_LSR_THRE) {
			ch->ch_cached_lsr &= ~(UART_LSR_THRE);

			writeb(ch->ch_wqueue[ch->ch_w_tail], &ch->ch_neo_uart->txrx);
			jsm_printk(WRITE, INFO, &ch->ch_bd->pci_dev,
					"Tx data: %x\n", ch->ch_wqueue[ch->ch_w_head]);
			ch->ch_w_tail++;
			ch->ch_w_tail &= WQUEUEMASK;
			ch->ch_txcount++;
		}
		return;
	}

	/*
	 * We have to do it this way, because of the EXAR TXFIFO count bug.
	 */
	if (!(ch->ch_flags & (CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM)))
		return;

	n = UART_17158_TX_FIFOSIZE - ch->ch_t_tlevel;

	/* cache head and tail of queue */
	head = ch->ch_w_head & WQUEUEMASK;
	tail = ch->ch_w_tail & WQUEUEMASK;
	qlen = (head - tail) & WQUEUEMASK;

	/* Find minimum of the FIFO space, versus queue length */
	n = min(n, qlen);

	while (n > 0) {

		s = ((head >= tail) ? head : WQUEUESIZE) - tail;
		s = min(s, n);

		if (s <= 0)
			break;

		memcpy_toio(&ch->ch_neo_uart->txrxburst, ch->ch_wqueue + tail, s);
		/* Add and flip queue if needed */
		tail = (tail + s) & WQUEUEMASK;
		n -= s;
		ch->ch_txcount += s;
		len_written += s;
	}

	/* Update the final tail */
	ch->ch_w_tail = tail & WQUEUEMASK;

	if (len_written >= ch->ch_t_tlevel)
		ch->ch_flags &= ~(CH_TX_FIFO_EMPTY | CH_TX_FIFO_LWM);

	if (!jsm_tty_write(&ch->uart_port))
		uart_write_wakeup(&ch->uart_port);
}