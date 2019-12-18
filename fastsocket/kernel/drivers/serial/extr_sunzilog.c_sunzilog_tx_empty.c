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

/* Variables and functions */
 unsigned int TIOCSER_TEMT ; 
 unsigned char Tx_BUF_EMP ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 unsigned char sunzilog_read_channel_status (struct uart_port*) ; 

__attribute__((used)) static unsigned int sunzilog_tx_empty(struct uart_port *port)
{
	unsigned long flags;
	unsigned char status;
	unsigned int ret;

	spin_lock_irqsave(&port->lock, flags);

	status = sunzilog_read_channel_status(port);

	spin_unlock_irqrestore(&port->lock, flags);

	if (status & Tx_BUF_EMP)
		ret = TIOCSER_TEMT;
	else
		ret = 0;

	return ret;
}