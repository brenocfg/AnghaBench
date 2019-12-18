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
struct msp71xx_gpio_chip {int /*<<< orphan*/  data_reg; } ;
struct gpio_chip {int dummy; } ;

/* Variables and functions */
 int __raw_readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gpio_lock ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 struct msp71xx_gpio_chip* to_msp71xx_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static void msp71xx_gpio_set(struct gpio_chip *chip, unsigned offset, int value)
{
	struct msp71xx_gpio_chip *msp_chip = to_msp71xx_gpio_chip(chip);
	unsigned long flags;
	u32 data;

	spin_lock_irqsave(&gpio_lock, flags);

	data = __raw_readl(msp_chip->data_reg);
	if (value)
		data |= (1 << offset);
	else
		data &= ~(1 << offset);
	__raw_writel(data, msp_chip->data_reg);

	spin_unlock_irqrestore(&gpio_lock, flags);
}