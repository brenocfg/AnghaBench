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
struct zs_scc {int initialised; int /*<<< orphan*/  zlock; } ;
struct zs_port {int /*<<< orphan*/  regs; struct zs_scc* scc; } ;

/* Variables and functions */
 int /*<<< orphan*/  FHWRES ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  irqs_disabled_flags (unsigned long) ; 
 int /*<<< orphan*/  load_zsregs (struct zs_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_zsreg (struct zs_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  write_zsreg (struct zs_port*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zs_line_drain (struct zs_port*,int) ; 

__attribute__((used)) static void zs_reset(struct zs_port *zport)
{
	struct zs_scc *scc = zport->scc;
	int irq;
	unsigned long flags;

	spin_lock_irqsave(&scc->zlock, flags);
	irq = !irqs_disabled_flags(flags);
	if (!scc->initialised) {
		/* Reset the pointer first, just in case...  */
		read_zsreg(zport, R0);
		/* And let the current transmission finish.  */
		zs_line_drain(zport, irq);
		write_zsreg(zport, R9, FHWRES);
		udelay(10);
		write_zsreg(zport, R9, 0);
		scc->initialised = 1;
	}
	load_zsregs(zport, zport->regs, irq);
	spin_unlock_irqrestore(&scc->zlock, flags);
}