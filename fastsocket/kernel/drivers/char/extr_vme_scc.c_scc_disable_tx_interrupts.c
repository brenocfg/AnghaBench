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
struct TYPE_3__ {int /*<<< orphan*/  flags; } ;
struct TYPE_4__ {TYPE_1__ port; } ;
struct scc_port {TYPE_2__ gs; } ;

/* Variables and functions */
 int /*<<< orphan*/  GS_TX_INTEN ; 
 int /*<<< orphan*/  IDR_TX_INT_ENAB ; 
 int /*<<< orphan*/  INT_AND_DMA_REG ; 
 int /*<<< orphan*/  SCC_ACCESS_INIT (struct scc_port*) ; 
 int /*<<< orphan*/  SCCmod (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 

__attribute__((used)) static void scc_disable_tx_interrupts(void *ptr)
{
	struct scc_port *port = ptr;
	unsigned long	flags;
	SCC_ACCESS_INIT(port);

	local_irq_save(flags);
	SCCmod(INT_AND_DMA_REG, ~IDR_TX_INT_ENAB, 0);
	port->gs.port.flags &= ~GS_TX_INTEN;
	local_irq_restore(flags);
}