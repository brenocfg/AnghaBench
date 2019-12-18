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
struct bridge_controller {TYPE_1__* base; } ;
typedef  int /*<<< orphan*/  cpuid_t ;
struct TYPE_2__ {int b_int_enable; int /*<<< orphan*/  b_wid_tflush; } ;
typedef  TYPE_1__ bridge_t ;

/* Variables and functions */
 struct bridge_controller* IRQ_TO_BRIDGE (unsigned int) ; 
 int SLOT_FROM_PCI_IRQ (unsigned int) ; 
 int find_level (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  intr_disconnect_level (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pr_debug (char*,unsigned int) ; 

__attribute__((used)) static void shutdown_bridge_irq(unsigned int irq)
{
	struct bridge_controller *bc = IRQ_TO_BRIDGE(irq);
	bridge_t *bridge = bc->base;
	int pin, swlevel;
	cpuid_t cpu;

	pr_debug("bridge_shutdown: irq 0x%x\n", irq);
	pin = SLOT_FROM_PCI_IRQ(irq);

	/*
	 * map irq to a swlevel greater than 6 since the first 6 bits
	 * of INT_PEND0 are taken
	 */
	swlevel = find_level(&cpu, irq);
	intr_disconnect_level(cpu, swlevel);

	bridge->b_int_enable &= ~(1 << pin);
	bridge->b_wid_tflush;
}