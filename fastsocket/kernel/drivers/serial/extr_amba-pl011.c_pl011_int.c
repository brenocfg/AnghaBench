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
struct TYPE_2__ {int /*<<< orphan*/  lock; scalar_t__ membase; } ;
struct uart_amba_port {TYPE_1__ port; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int AMBA_ISR_PASS_LIMIT ; 
 int /*<<< orphan*/  IRQ_RETVAL (int) ; 
 unsigned int UART011_CTSMIS ; 
 unsigned int UART011_DCDMIS ; 
 unsigned int UART011_DSRMIS ; 
 scalar_t__ UART011_ICR ; 
 scalar_t__ UART011_MIS ; 
 unsigned int UART011_RIMIS ; 
 unsigned int UART011_RTIS ; 
 unsigned int UART011_RXIS ; 
 unsigned int UART011_TXIS ; 
 int /*<<< orphan*/  pl011_modem_status (struct uart_amba_port*) ; 
 int /*<<< orphan*/  pl011_rx_chars (struct uart_amba_port*) ; 
 int /*<<< orphan*/  pl011_tx_chars (struct uart_amba_port*) ; 
 unsigned int readw (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  writew (unsigned int,scalar_t__) ; 

__attribute__((used)) static irqreturn_t pl011_int(int irq, void *dev_id)
{
	struct uart_amba_port *uap = dev_id;
	unsigned int status, pass_counter = AMBA_ISR_PASS_LIMIT;
	int handled = 0;

	spin_lock(&uap->port.lock);

	status = readw(uap->port.membase + UART011_MIS);
	if (status) {
		do {
			writew(status & ~(UART011_TXIS|UART011_RTIS|
					  UART011_RXIS),
			       uap->port.membase + UART011_ICR);

			if (status & (UART011_RTIS|UART011_RXIS))
				pl011_rx_chars(uap);
			if (status & (UART011_DSRMIS|UART011_DCDMIS|
				      UART011_CTSMIS|UART011_RIMIS))
				pl011_modem_status(uap);
			if (status & UART011_TXIS)
				pl011_tx_chars(uap);

			if (pass_counter-- == 0)
				break;

			status = readw(uap->port.membase + UART011_MIS);
		} while (status != 0);
		handled = 1;
	}

	spin_unlock(&uap->port.lock);

	return IRQ_RETVAL(handled);
}