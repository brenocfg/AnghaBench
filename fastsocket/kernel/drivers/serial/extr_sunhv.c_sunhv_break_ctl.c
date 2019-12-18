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
 int /*<<< orphan*/  CON_BREAK ; 
 long HV_EOK ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 long sun4v_con_putchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void sunhv_break_ctl(struct uart_port *port, int break_state)
{
	if (break_state) {
		unsigned long flags;
		int limit = 10000;

		spin_lock_irqsave(&port->lock, flags);

		while (limit-- > 0) {
			long status = sun4v_con_putchar(CON_BREAK);
			if (status == HV_EOK)
				break;
			udelay(1);
		}

		spin_unlock_irqrestore(&port->lock, flags);
	}
}