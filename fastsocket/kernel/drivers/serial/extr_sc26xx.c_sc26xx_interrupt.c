#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct uart_sc26xx_port {TYPE_1__* port; } ;
struct tty_struct {int dummy; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  ISR ; 
 int ISR_RXRDYA ; 
 int ISR_RXRDYB ; 
 int ISR_TXRDYA ; 
 int ISR_TXRDYB ; 
 int READ_SC (TYPE_1__*,int /*<<< orphan*/ ) ; 
 struct tty_struct* receive_chars (TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  transmit_chars (TYPE_1__*) ; 
 int /*<<< orphan*/  tty_flip_buffer_push (struct tty_struct*) ; 

__attribute__((used)) static irqreturn_t sc26xx_interrupt(int irq, void *dev_id)
{
	struct uart_sc26xx_port *up = dev_id;
	struct tty_struct *tty;
	unsigned long flags;
	u8 isr;

	spin_lock_irqsave(&up->port[0].lock, flags);

	tty = NULL;
	isr = READ_SC(&up->port[0], ISR);
	if (isr & ISR_TXRDYA)
	    transmit_chars(&up->port[0]);
	if (isr & ISR_RXRDYA)
	    tty = receive_chars(&up->port[0]);

	spin_unlock(&up->port[0].lock);

	if (tty)
		tty_flip_buffer_push(tty);

	spin_lock(&up->port[1].lock);

	tty = NULL;
	if (isr & ISR_TXRDYB)
	    transmit_chars(&up->port[1]);
	if (isr & ISR_RXRDYB)
	    tty = receive_chars(&up->port[1]);

	spin_unlock_irqrestore(&up->port[1].lock, flags);

	if (tty)
		tty_flip_buffer_push(tty);

	return IRQ_HANDLED;
}