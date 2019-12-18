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
 scalar_t__ UART010_IIR ; 
 unsigned int UART010_IIR_MIS ; 
 unsigned int UART010_IIR_RIS ; 
 unsigned int UART010_IIR_RTIS ; 
 unsigned int UART010_IIR_TIS ; 
 int /*<<< orphan*/  pl010_modem_status (struct uart_amba_port*) ; 
 int /*<<< orphan*/  pl010_rx_chars (struct uart_amba_port*) ; 
 int /*<<< orphan*/  pl010_tx_chars (struct uart_amba_port*) ; 
 unsigned int readb (scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static irqreturn_t pl010_int(int irq, void *dev_id)
{
	struct uart_amba_port *uap = dev_id;
	unsigned int status, pass_counter = AMBA_ISR_PASS_LIMIT;
	int handled = 0;

	spin_lock(&uap->port.lock);

	status = readb(uap->port.membase + UART010_IIR);
	if (status) {
		do {
			if (status & (UART010_IIR_RTIS | UART010_IIR_RIS))
				pl010_rx_chars(uap);
			if (status & UART010_IIR_MIS)
				pl010_modem_status(uap);
			if (status & UART010_IIR_TIS)
				pl010_tx_chars(uap);

			if (pass_counter-- == 0)
				break;

			status = readb(uap->port.membase + UART010_IIR);
		} while (status & (UART010_IIR_RTIS | UART010_IIR_RIS |
				   UART010_IIR_TIS));
		handled = 1;
	}

	spin_unlock(&uap->port.lock);

	return IRQ_RETVAL(handled);
}