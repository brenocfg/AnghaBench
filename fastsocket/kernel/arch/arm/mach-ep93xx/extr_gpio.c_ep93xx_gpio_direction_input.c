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
typedef  int u8 ;
struct gpio_chip {int dummy; } ;
struct ep93xx_gpio_chip {int /*<<< orphan*/  data_dir_reg; } ;

/* Variables and functions */
 int __raw_readb (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __raw_writeb (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 struct ep93xx_gpio_chip* to_ep93xx_gpio_chip (struct gpio_chip*) ; 

__attribute__((used)) static int ep93xx_gpio_direction_input(struct gpio_chip *chip, unsigned offset)
{
	struct ep93xx_gpio_chip *ep93xx_chip = to_ep93xx_gpio_chip(chip);
	unsigned long flags;
	u8 v;

	local_irq_save(flags);
	v = __raw_readb(ep93xx_chip->data_dir_reg);
	v &= ~(1 << offset);
	__raw_writeb(v, ep93xx_chip->data_dir_reg);
	local_irq_restore(flags);

	return 0;
}