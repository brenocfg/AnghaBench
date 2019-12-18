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
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct uart_sunsu_port {TYPE_1__ port; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  UART_IIR ; 
 int UART_IIR_NO_INT ; 
 int /*<<< orphan*/  UART_LSR ; 
 unsigned char UART_LSR_DR ; 
 unsigned char UART_LSR_THRE ; 
 int /*<<< orphan*/  check_modem_status (struct uart_sunsu_port*) ; 
 struct tty_struct* receive_chars (struct uart_sunsu_port*,unsigned char*) ; 
 int serial_in (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 unsigned char serial_inp (struct uart_sunsu_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_sunsu_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 

__attribute__((used)) static irqreturn_t sunsu_serial_interrupt(int irq, void *dev_id)
{
	struct uart_sunsu_port *up = dev_id;
	unsigned long flags;
	unsigned char status;

	spin_lock_irqsave(&up->port.lock, flags);

	do {
		struct tty_struct *tty;

		status = serial_inp(up, UART_LSR);
		tty = NULL;
		if (status & UART_LSR_DR)
			tty = receive_chars(up, &status);
		check_modem_status(up);
		if (status & UART_LSR_THRE)
			transmit_chars(up);

		spin_unlock_irqrestore(&up->port.lock, flags);

		if (tty)
			tty_flip_buffer_push(tty);

		spin_lock_irqsave(&up->port.lock, flags);

	} while (!(serial_in(up, UART_IIR) & UART_IIR_NO_INT));

	spin_unlock_irqrestore(&up->port.lock, flags);

	return IRQ_HANDLED;
}