#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct uart_port {int /*<<< orphan*/  lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  irq; } ;
struct uart_pmac_port {int* curregs; int /*<<< orphan*/  mate; int /*<<< orphan*/  flags; TYPE_1__ port; int /*<<< orphan*/ * node; } ;
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int EXT_INT_ENAB ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_IS_IRQ_ON ; 
 int /*<<< orphan*/  PMACZILOG_FLAG_IS_OPEN ; 
 size_t R1 ; 
 size_t R3 ; 
 size_t R5 ; 
 int RxENABLE ; 
 int RxINT_MASK ; 
 int SND_BRK ; 
 int TxENABLE ; 
 int TxINT_ENAB ; 
 scalar_t__ ZS_IS_ASLEEP (struct uart_pmac_port*) ; 
 scalar_t__ ZS_IS_CONS (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  ZS_IS_OPEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct uart_pmac_port*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pmz_debug (char*) ; 
 TYPE_2__* pmz_get_port_A (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_irq_mutex ; 
 int /*<<< orphan*/  pmz_maybe_update_regs (struct uart_pmac_port*) ; 
 int /*<<< orphan*/  pmz_set_scc_power (struct uart_pmac_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct uart_pmac_port* to_pmz (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct uart_pmac_port*,size_t,int) ; 
 int /*<<< orphan*/  zssync (struct uart_pmac_port*) ; 

__attribute__((used)) static void pmz_shutdown(struct uart_port *port)
{
	struct uart_pmac_port *uap = to_pmz(port);
	unsigned long flags;

	pmz_debug("pmz: shutdown()\n");

	if (uap->node == NULL)
		return;

	mutex_lock(&pmz_irq_mutex);

	/* Release interrupt handler */
       	free_irq(uap->port.irq, uap);

	spin_lock_irqsave(&port->lock, flags);

	uap->flags &= ~PMACZILOG_FLAG_IS_OPEN;

	if (!ZS_IS_OPEN(uap->mate))
		pmz_get_port_A(uap)->flags &= ~PMACZILOG_FLAG_IS_IRQ_ON;

	/* Disable interrupts */
	if (!ZS_IS_ASLEEP(uap)) {
		uap->curregs[R1] &= ~(EXT_INT_ENAB | TxINT_ENAB | RxINT_MASK);
		write_zsreg(uap, R1, uap->curregs[R1]);
		zssync(uap);
	}

	if (ZS_IS_CONS(uap) || ZS_IS_ASLEEP(uap)) {
		spin_unlock_irqrestore(&port->lock, flags);
		mutex_unlock(&pmz_irq_mutex);
		return;
	}

	/* Disable receiver and transmitter.  */
	uap->curregs[R3] &= ~RxENABLE;
	uap->curregs[R5] &= ~TxENABLE;

	/* Disable all interrupts and BRK assertion.  */
	uap->curregs[R5] &= ~SND_BRK;
	pmz_maybe_update_regs(uap);

	/* Shut the chip down */
	pmz_set_scc_power(uap, 0);

	spin_unlock_irqrestore(&port->lock, flags);

	mutex_unlock(&pmz_irq_mutex);

	pmz_debug("pmz: shutdown() done.\n");
}