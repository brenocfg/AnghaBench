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
struct TYPE_2__ {int line; } ;
struct dz_port {TYPE_1__ port; } ;

/* Variables and functions */
 int /*<<< orphan*/  DZ_TCR ; 
 unsigned short dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,unsigned short) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_break_ctl(struct uart_port *uport, int break_state)
{
	/*
	 * FIXME: Can't access BREAK bits in TDR easily;
	 * reuse the code for polled TX. --macro
	 */
	struct dz_port *dport = to_dport(uport);
	unsigned long flags;
	unsigned short tmp, mask = 1 << dport->port.line;

	spin_lock_irqsave(&uport->lock, flags);
	tmp = dz_in(dport, DZ_TCR);
	if (break_state)
		tmp |= mask;
	else
		tmp &= ~mask;
	dz_out(dport, DZ_TCR, tmp);
	spin_unlock_irqrestore(&uport->lock, flags);
}