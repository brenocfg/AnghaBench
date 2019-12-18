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
typedef  int u32 ;

/* Variables and functions */
 scalar_t__ ARM_RESET_REGISTER ; 
 scalar_t__ SPU_REGISTER_BASE ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  spu_write_wait () ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static void spu_disable(void)
{
	int i;
	unsigned long flags;
	u32 regval;
	spu_write_wait();
	regval = readl(ARM_RESET_REGISTER);
	regval |= 1;
	spu_write_wait();
	local_irq_save(flags);
	writel(regval, ARM_RESET_REGISTER);
	local_irq_restore(flags);
	for (i = 0; i < 64; i++) {
		spu_write_wait();
		regval = readl(SPU_REGISTER_BASE + (i * 0x80));
		regval = (regval & ~0x4000) | 0x8000;
		spu_write_wait();
		local_irq_save(flags);
		writel(regval, SPU_REGISTER_BASE + (i * 0x80));
		local_irq_restore(flags);
	}
}