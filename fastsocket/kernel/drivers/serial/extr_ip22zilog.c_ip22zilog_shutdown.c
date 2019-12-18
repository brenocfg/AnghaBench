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
struct zilog_channel {int dummy; } ;
struct uart_port {int /*<<< orphan*/  lock; } ;
struct uart_ip22zilog_port {int* curregs; } ;

/* Variables and functions */
 int EXT_INT_ENAB ; 
 size_t R1 ; 
 size_t R3 ; 
 size_t R5 ; 
 int RxENAB ; 
 int RxINT_MASK ; 
 int SND_BRK ; 
 int TxENAB ; 
 int TxINT_ENAB ; 
 struct uart_ip22zilog_port* UART_ZILOG (struct uart_port*) ; 
 struct zilog_channel* ZILOG_CHANNEL_FROM_PORT (struct uart_port*) ; 
 scalar_t__ ZS_IS_CONS (struct uart_ip22zilog_port*) ; 
 int /*<<< orphan*/  ip22zilog_maybe_update_regs (struct uart_ip22zilog_port*,struct zilog_channel*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void ip22zilog_shutdown(struct uart_port *port)
{
	struct uart_ip22zilog_port *up = UART_ZILOG(port);
	struct zilog_channel *channel;
	unsigned long flags;

	if (ZS_IS_CONS(up))
		return;

	spin_lock_irqsave(&port->lock, flags);

	channel = ZILOG_CHANNEL_FROM_PORT(port);

	/* Disable receiver and transmitter.  */
	up->curregs[R3] &= ~RxENAB;
	up->curregs[R5] &= ~TxENAB;

	/* Disable all interrupts and BRK assertion.  */
	up->curregs[R1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	up->curregs[R5] &= ~SND_BRK;
	ip22zilog_maybe_update_regs(up, channel);

	spin_unlock_irqrestore(&port->lock, flags);
}