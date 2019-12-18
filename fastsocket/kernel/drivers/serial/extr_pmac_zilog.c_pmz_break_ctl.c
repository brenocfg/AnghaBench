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
struct uart_pmac_port {unsigned char* curregs; int /*<<< orphan*/ * node; } ;

/* Variables and functions */
 size_t R5 ; 
 unsigned char SND_BRK ; 
 scalar_t__ ZS_IS_ASLEEP (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,unsigned char) ; 

__attribute__((used)) static void pmz_break_ctl(struct uart_port *port, int break_state)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned char set_bits, clear_bits, new_reg;
	unsigned long flags;

	if (uap->node == NULL)
		return;
	set_bits = clear_bits = 0;

	if (break_state)
		set_bits |= SND_BRK;
	else
		clear_bits |= SND_BRK;

	spin_lock_irqsave(&port->lock, flags);

	new_reg = (uap->curregs[R5] | set_bits) & ~clear_bits;
	if (new_reg != uap->curregs[R5]) {
		uap->curregs[R5] = new_reg;

		/* NOTE: Not subject to 'transmitter active' rule.  */ 
		if (ZS_IS_ASLEEP(uap))
			return;
		write_zsreg(uap, R5, uap->curregs[R5]);
	}

	spin_unlock_irqrestore(&port->lock, flags);
}