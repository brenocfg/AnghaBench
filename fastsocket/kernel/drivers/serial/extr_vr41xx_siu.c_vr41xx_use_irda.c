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
typedef  int /*<<< orphan*/  uint8_t ;
struct uart_port {int /*<<< orphan*/  lock; } ;
typedef  scalar_t__ irda_use_t ;

/* Variables and functions */
 scalar_t__ FIR_USE_IRDA ; 
 int /*<<< orphan*/  IRUSESEL ; 
 int /*<<< orphan*/  SIUIRSEL ; 
 int /*<<< orphan*/  siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 struct uart_port* siu_uart_ports ; 
 int /*<<< orphan*/  siu_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

void vr41xx_use_irda(irda_use_t use)
{
	struct uart_port *port;
	unsigned long flags;
	uint8_t irsel;

	port = &siu_uart_ports[0];

	spin_lock_irqsave(&port->lock, flags);

	irsel = siu_read(port, SIUIRSEL);
	if (use == FIR_USE_IRDA)
		irsel |= IRUSESEL;
	else
		irsel &= ~IRUSESEL;
	siu_write(port, SIUIRSEL, irsel);

	spin_unlock_irqrestore(&port->lock, flags);
}