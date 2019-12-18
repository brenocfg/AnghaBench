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
struct mtip_port {int command_list_dma; int rxfis_dma; scalar_t__ mmio; TYPE_1__* dd; scalar_t__* completed; } ;
struct TYPE_2__ {int slot_groups; scalar_t__ mmio; } ;

/* Variables and functions */
 int DEF_PORT_IRQ ; 
 scalar_t__ HOST_CAP ; 
 int HOST_CAP_64 ; 
 scalar_t__ HOST_IRQ_STAT ; 
 scalar_t__ PORT_FIS_ADDR ; 
 scalar_t__ PORT_FIS_ADDR_HI ; 
 scalar_t__ PORT_IRQ_MASK ; 
 scalar_t__ PORT_IRQ_STAT ; 
 scalar_t__ PORT_LST_ADDR ; 
 scalar_t__ PORT_LST_ADDR_HI ; 
 scalar_t__ PORT_SCR_ERR ; 
 int /*<<< orphan*/  mtip_deinit_port (struct mtip_port*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void mtip_init_port(struct mtip_port *port)
{
	int i;
	mtip_deinit_port(port);

	/* Program the command list base and FIS base addresses */
	if (readl(port->dd->mmio + HOST_CAP) & HOST_CAP_64) {
		writel((port->command_list_dma >> 16) >> 16,
			 port->mmio + PORT_LST_ADDR_HI);
		writel((port->rxfis_dma >> 16) >> 16,
			 port->mmio + PORT_FIS_ADDR_HI);
	}

	writel(port->command_list_dma & 0xFFFFFFFF,
			port->mmio + PORT_LST_ADDR);
	writel(port->rxfis_dma & 0xFFFFFFFF, port->mmio + PORT_FIS_ADDR);

	/* Clear SError */
	writel(readl(port->mmio + PORT_SCR_ERR), port->mmio + PORT_SCR_ERR);

	/* reset the completed registers.*/
	for (i = 0; i < port->dd->slot_groups; i++)
		writel(0xFFFFFFFF, port->completed[i]);

	/* Clear any pending interrupts for this port */
	writel(readl(port->mmio + PORT_IRQ_STAT), port->mmio + PORT_IRQ_STAT);

	/* Clear any pending interrupts on the HBA. */
	writel(readl(port->dd->mmio + HOST_IRQ_STAT),
					port->dd->mmio + HOST_IRQ_STAT);

	/* Enable port interrupts */
	writel(DEF_PORT_IRQ, port->mmio + PORT_IRQ_MASK);
}