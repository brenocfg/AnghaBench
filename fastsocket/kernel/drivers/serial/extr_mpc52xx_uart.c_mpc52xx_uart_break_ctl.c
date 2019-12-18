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
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_2__ {int /*<<< orphan*/  command; } ;

/* Variables and functions */
 int /*<<< orphan*/  MPC52xx_PSC_START_BRK ; 
 int /*<<< orphan*/  MPC52xx_PSC_STOP_BRK ; 
 TYPE_1__* PSC (struct uart_port*) ; 
 int /*<<< orphan*/  out_8 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void
mpc52xx_uart_break_ctl(struct uart_port *port, int ctl)
{
	unsigned long flags;
	spin_lock_irqsave(&port->lock, flags);

	if (ctl == -1)
		out_8(&PSC(port)->command, MPC52xx_PSC_START_BRK);
	else
		out_8(&PSC(port)->command, MPC52xx_PSC_STOP_BRK);

	spin_unlock_irqrestore(&port->lock, flags);
}