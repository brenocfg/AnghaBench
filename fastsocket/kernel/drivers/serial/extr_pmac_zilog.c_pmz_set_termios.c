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
struct uart_pmac_port {int* curregs; } ;
struct ktermios {int dummy; } ;

/* Variables and functions */
 int EXT_INT_ENAB ; 
 int INT_ALL_Rx ; 
 size_t R1 ; 
 int RxINT_MASK ; 
 int TxINT_ENAB ; 
 int /*<<< orphan*/  ZS_IS_EXTCLK (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_OPEN (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  __pmz_set_termios (struct uart_port*,struct ktermios*,struct ktermios*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,int) ; 

__attribute__((used)) static void pmz_set_termios(struct uart_port *port, struct ktermios *termios,
			    struct ktermios *old)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long flags;

	spin_lock_irqsave(&port->lock, flags);	

	/* Disable IRQs on the port */
	uap->curregs[R1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
	write_zsreg(uap, R1, uap->curregs[R1]);

	/* Setup new port configuration */
	__pmz_set_termios(port, termios, old);

	/* Re-enable IRQs on the port */
	if (ZS_IS_OPEN(uap)) {
		uap->curregs[R1] |= INT_ALL_Rx | TxINT_ENAB;
		if (!ZS_IS_EXTCLK(uap))
			uap->curregs[R1] |= EXT_INT_ENAB;
		write_zsreg(uap, R1, uap->curregs[R1]);
	}
	spin_unlock_irqrestore(&port->lock, flags);
}