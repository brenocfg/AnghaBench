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
struct tty_struct {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  rx; } ;
struct TYPE_8__ {scalar_t__ ignore_status_mask; int /*<<< orphan*/  lock; TYPE_3__ icount; TYPE_2__* state; } ;
struct nwpserial_port {TYPE_4__ port; int /*<<< orphan*/  dcr_host; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_5__ {struct tty_struct* tty; } ;
struct TYPE_6__ {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 scalar_t__ NWPSERIAL_STATUS_RXVALID ; 
 int /*<<< orphan*/  TTY_NORMAL ; 
 int /*<<< orphan*/  UART_IIR ; 
 int /*<<< orphan*/  UART_LSR ; 
 int UART_LSR_DR ; 
 int /*<<< orphan*/  UART_RX ; 
 int dcr_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dcr_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 
 int /*<<< orphan*/  tty_insert_flip_char (struct tty_struct*,unsigned char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t nwpserial_interrupt(int irq, void *dev_id)
{
	struct nwpserial_port *up = dev_id;
	struct tty_struct *tty = up->port.state->port.tty;
	irqreturn_t ret;
	unsigned int iir;
	unsigned char ch;

	spin_lock(&up->port.lock);

	/* check if the uart was the interrupt source. */
	iir = dcr_read(up->dcr_host, UART_IIR);
	if (!iir) {
		ret = IRQ_NONE;
		goto out;
	}

	do {
		up->port.icount.rx++;
		ch = dcr_read(up->dcr_host, UART_RX);
		if (up->port.ignore_status_mask != NWPSERIAL_STATUS_RXVALID)
			tty_insert_flip_char(tty, ch, TTY_NORMAL);
	} while (dcr_read(up->dcr_host, UART_LSR) & UART_LSR_DR);

	tty_flip_buffer_push(tty);
	ret = IRQ_HANDLED;

	/* clear interrupt */
	dcr_write(up->dcr_host, UART_IIR, 1);
out:
	spin_unlock(&up->port.lock);
	return ret;
}