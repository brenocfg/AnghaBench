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
struct gpio_chip {unsigned int ngpio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int GPIO_CTL_HI_REG ; 
 int GPIO_CTL_LO_REG ; 
 int GPIO_DIR_IN ; 
 int /*<<< orphan*/  bcm63xx_gpio_lock ; 
 int bcm_gpio_readl (int) ; 
 int /*<<< orphan*/  bcm_gpio_writel (int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int bcm63xx_gpio_set_direction(struct gpio_chip *chip,
				      unsigned gpio, int dir)
{
	u32 reg;
	u32 mask;
	u32 tmp;
	unsigned long flags;

	if (gpio >= chip->ngpio)
		BUG();

	if (gpio < 32) {
		reg = GPIO_CTL_LO_REG;
		mask = 1 << gpio;
	} else {
		reg = GPIO_CTL_HI_REG;
		mask = 1 << (gpio - 32);
	}

	spin_lock_irqsave(&bcm63xx_gpio_lock, flags);
	tmp = bcm_gpio_readl(reg);
	if (dir == GPIO_DIR_IN)
		tmp &= ~mask;
	else
		tmp |= mask;
	bcm_gpio_writel(tmp, reg);
	spin_unlock_irqrestore(&bcm63xx_gpio_lock, flags);

	return 0;
}