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
struct irq_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_IRQ (char*,unsigned int) ; 
 int /*<<< orphan*/  NETX_DPMAS_INT_EN ; 
 int /*<<< orphan*/  NETX_DPMAS_INT_STAT ; 
 unsigned int NETX_IRQ_HIF_CHAINED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generic_handle_irq (unsigned int) ; 
 int readl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
netx_hif_demux_handler(unsigned int irq_unused, struct irq_desc *desc)
{
	unsigned int irq = NETX_IRQ_HIF_CHAINED(0);
	unsigned int stat;

	stat = ((readl(NETX_DPMAS_INT_EN) &
		readl(NETX_DPMAS_INT_STAT)) >> 24) & 0x1f;

	while (stat) {
		if (stat & 1) {
			DEBUG_IRQ("handling irq %d\n", irq);
			generic_handle_irq(irq);
		}
		irq++;
		stat >>= 1;
	}
}