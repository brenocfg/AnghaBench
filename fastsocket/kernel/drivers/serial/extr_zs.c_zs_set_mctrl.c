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
typedef  int /*<<< orphan*/  u8 ;
struct zs_scc {int /*<<< orphan*/  zlock; struct zs_port* zport; } ;
struct zs_port {int /*<<< orphan*/ * regs; struct zs_scc* scc; } ;
struct uart_port {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DTR ; 
 int /*<<< orphan*/  LOOPBAK ; 
 int /*<<< orphan*/  R14 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  RTS ; 
 unsigned int TIOCM_DTR ; 
 unsigned int TIOCM_LOOP ; 
 unsigned int TIOCM_RTS ; 
 size_t ZS_CHAN_A ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 struct zs_port* to_zport (struct uart_port*) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void zs_set_mctrl(struct uart_port *uport, unsigned int mctrl)
{
	struct zs_port *zport = to_zport(uport);
	struct zs_scc *scc = zport->scc;
	struct zs_port *zport_a = &scc->zport[ZS_CHAN_A];
	u8 oldloop, newloop;

	spin_lock(&scc->zlock);
	if (zport != zport_a) {
		if (mctrl & TIOCM_DTR)
			zport_a->regs[5] |= DTR;
		else
			zport_a->regs[5] &= ~DTR;
		if (mctrl & TIOCM_RTS)
			zport_a->regs[5] |= RTS;
		else
			zport_a->regs[5] &= ~RTS;
		write_zsreg(zport_a, R5, zport_a->regs[5]);
	}

	/* Rarely modified, so don't poke at hardware unless necessary. */
	oldloop = zport->regs[14];
	newloop = oldloop;
	if (mctrl & TIOCM_LOOP)
		newloop |= LOOPBAK;
	else
		newloop &= ~LOOPBAK;
	if (newloop != oldloop) {
		zport->regs[14] = newloop;
		write_zsreg(zport, R14, zport->regs[14]);
	}
	spin_unlock(&scc->zlock);
}