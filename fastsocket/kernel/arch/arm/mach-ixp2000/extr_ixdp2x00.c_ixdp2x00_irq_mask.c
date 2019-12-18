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
struct slowport_cfg {int dummy; } ;

/* Variables and functions */
 unsigned long IXP2000_BOARD_IRQ_MASK (unsigned int) ; 
 unsigned long* board_irq_mask ; 
 int /*<<< orphan*/  ixp2000_acquire_slowport (int /*<<< orphan*/ *,struct slowport_cfg*) ; 
 int /*<<< orphan*/  ixp2000_reg_wrb (unsigned long*,unsigned long) ; 
 int /*<<< orphan*/  ixp2000_release_slowport (struct slowport_cfg*) ; 
 scalar_t__ machine_is_ixdp2400 () ; 
 int /*<<< orphan*/  slowport_cpld_cfg ; 

__attribute__((used)) static void ixdp2x00_irq_mask(unsigned int irq)
{
	unsigned long dummy;
	static struct slowport_cfg old_cfg;

	/*
	 * This is ugly in common code but really don't know
	 * of a better way to handle it. :(
	 */
#ifdef CONFIG_ARCH_IXDP2400
	if (machine_is_ixdp2400())
		ixp2000_acquire_slowport(&slowport_cpld_cfg, &old_cfg);
#endif

	dummy = *board_irq_mask;
	dummy |=  IXP2000_BOARD_IRQ_MASK(irq);
	ixp2000_reg_wrb(board_irq_mask, dummy);

#ifdef CONFIG_ARCH_IXDP2400
	if (machine_is_ixdp2400())
		ixp2000_release_slowport(&old_cfg);
#endif
}