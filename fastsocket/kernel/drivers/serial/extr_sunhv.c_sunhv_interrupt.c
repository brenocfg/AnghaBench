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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 struct tty_struct* receive_chars (struct uart_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (struct uart_port*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 

__attribute__((used)) static irqreturn_t sunhv_interrupt(int irq, void *dev_id)
{
	struct uart_port *port = dev_id;
	struct tty_struct *tty;
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);
	tty = receive_chars(port);
	transmit_chars(port);
	spin_unlock_irqrestore(&port->lock, flags);

	if (tty)
		tty_flip_buffer_push(tty);

	return IRQ_HANDLED;
}