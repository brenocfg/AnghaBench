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
struct pnx8xxx_port {TYPE_1__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  PNX8XXX_ICLR ; 
 int /*<<< orphan*/  PNX8XXX_IEN ; 
 int /*<<< orphan*/  PNX8XXX_ISTAT ; 
 unsigned int PNX8XXX_UART_INT_BREAK ; 
 unsigned int PNX8XXX_UART_INT_RX ; 
 unsigned int PNX8XXX_UART_INT_TX ; 
 int /*<<< orphan*/  pnx8xxx_rx_chars (struct pnx8xxx_port*) ; 
 int /*<<< orphan*/  pnx8xxx_tx_chars (struct pnx8xxx_port*) ; 
 unsigned int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pnx8xxx_int(int irq, void *dev_id)
{
	struct pnx8xxx_port *sport = dev_id;
	unsigned int status;

	spin_lock(&sport->port.lock);
	/* Get the interrupts */
	status  = serial_in(sport, PNX8XXX_ISTAT) & serial_in(sport, PNX8XXX_IEN);

	/* Byte or break signal received */
	if (status & (PNX8XXX_UART_INT_RX | PNX8XXX_UART_INT_BREAK))
		pnx8xxx_rx_chars(sport);

	/* TX holding register empty - transmit a byte */
	if (status & PNX8XXX_UART_INT_TX)
		pnx8xxx_tx_chars(sport);

	/* Clear the ISTAT register */
	serial_out(sport, PNX8XXX_ICLR, status);

	spin_unlock(&sport->port.lock);
	return IRQ_HANDLED;
}