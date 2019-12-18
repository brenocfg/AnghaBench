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
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;
struct pnx8xxx_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  PNX8XXX_LCR ; 
 unsigned int PNX8XXX_UART_LCR_TXBREAK ; 
 unsigned int serial_in (struct pnx8xxx_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_out (struct pnx8xxx_port*,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void pnx8xxx_break_ctl(struct uart_port *port, int break_state)
{
	struct pnx8xxx_port *sport = (struct pnx8xxx_port *)port;
	unsigned long flags;
	unsigned int lcr;

	spin_lock_irqsave(&sport->port.lock, flags);
	lcr = serial_in(sport, PNX8XXX_LCR);
	if (break_state == -1)
		lcr |= PNX8XXX_UART_LCR_TXBREAK;
	else
		lcr &= ~PNX8XXX_UART_LCR_TXBREAK;
	serial_out(sport, PNX8XXX_LCR, lcr);
	spin_unlock_irqrestore(&sport->port.lock, flags);
}