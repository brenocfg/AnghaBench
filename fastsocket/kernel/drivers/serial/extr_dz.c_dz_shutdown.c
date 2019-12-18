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
typedef  int u16 ;
struct uart_port {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; int /*<<< orphan*/  lock; } ;
struct dz_port {TYPE_1__ port; struct dz_mux* mux; } ;
struct dz_mux {int /*<<< orphan*/  irq_guard; } ;

/* Variables and functions */
 int /*<<< orphan*/  DZ_CSR ; 
 int DZ_RIE ; 
 int DZ_TIE ; 
 int atomic_add_return (int,int /*<<< orphan*/ *) ; 
 int dz_in (struct dz_port*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dz_out (struct dz_port*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dz_stop_tx (TYPE_1__*) ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct dz_mux*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct dz_port* to_dport (struct uart_port*) ; 

__attribute__((used)) static void dz_shutdown(struct uart_port *uport)
{
	struct dz_port *dport = to_dport(uport);
	struct dz_mux *mux = dport->mux;
	unsigned long flags;
	int irq_guard;
	u16 tmp;

	spin_lock_irqsave(&dport->port.lock, flags);
	dz_stop_tx(&dport->port);
	spin_unlock_irqrestore(&dport->port.lock, flags);

	irq_guard = atomic_add_return(-1, &mux->irq_guard);
	if (!irq_guard) {
		/* Disable interrupts.  */
		tmp = dz_in(dport, DZ_CSR);
		tmp &= ~(DZ_RIE | DZ_TIE);
		dz_out(dport, DZ_CSR, tmp);

		free_irq(dport->port.irq, mux);
	}
}