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

/* Variables and functions */
 int /*<<< orphan*/  CPLD_FLASH_WR_ENABLE ; 
 int /*<<< orphan*/  nw_cpld_modify (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw_gpio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void kick_open(void)
{
	unsigned long flags;

	/*
	 * we want to write a bit pattern XXX1 to Xilinx to enable
	 * the write gate, which will be open for about the next 2ms.
	 */
	spin_lock_irqsave(&nw_gpio_lock, flags);
	nw_cpld_modify(CPLD_FLASH_WR_ENABLE, CPLD_FLASH_WR_ENABLE);
	spin_unlock_irqrestore(&nw_gpio_lock, flags);

	/*
	 * let the ISA bus to catch on...
	 */
	udelay(25);
}