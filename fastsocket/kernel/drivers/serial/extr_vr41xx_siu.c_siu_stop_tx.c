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

/* Variables and functions */
 int /*<<< orphan*/  UART_IER ; 
 int /*<<< orphan*/  UART_IER_THRI ; 
 int /*<<< orphan*/  siu_read (struct uart_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  siu_write (struct uart_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void siu_stop_tx(struct uart_port *port)
{
	unsigned long flags;
	uint8_t ier;

	spin_lock_irqsave(&port->lock, flags);

	ier = siu_read(port, UART_IER);
	ier &= ~UART_IER_THRI;
	siu_write(port, UART_IER, ier);

	spin_unlock_irqrestore(&port->lock, flags);
}