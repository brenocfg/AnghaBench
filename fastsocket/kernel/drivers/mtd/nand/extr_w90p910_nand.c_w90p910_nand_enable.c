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
struct w90p910_nand {int /*<<< orphan*/  lock; scalar_t__ reg; } ;

/* Variables and functions */
 unsigned int BUSWID ; 
 unsigned int DMARWEN ; 
 unsigned int ECC4EN ; 
 unsigned int NANDCS ; 
 unsigned int NAND_EN ; 
 unsigned int PSIZE ; 
 scalar_t__ REG_FMICSR ; 
 scalar_t__ REG_SMCSR ; 
 unsigned int RESET_FMI ; 
 unsigned int SWRST ; 
 unsigned int WP ; 
 unsigned int __raw_readl (scalar_t__) ; 
 int /*<<< orphan*/  __raw_writel (unsigned int,scalar_t__) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void w90p910_nand_enable(struct w90p910_nand *nand)
{
	unsigned int val;
	spin_lock(&nand->lock);
	__raw_writel(RESET_FMI, (nand->reg + REG_FMICSR));

	val = __raw_readl(nand->reg + REG_FMICSR);

	if (!(val & NAND_EN))
		__raw_writel(val | NAND_EN, REG_FMICSR);

	val = __raw_readl(nand->reg + REG_SMCSR);

	val &= ~(SWRST|PSIZE|DMARWEN|BUSWID|ECC4EN|NANDCS);
	val |= WP;

	__raw_writel(val, nand->reg + REG_SMCSR);

	spin_unlock(&nand->lock);
}