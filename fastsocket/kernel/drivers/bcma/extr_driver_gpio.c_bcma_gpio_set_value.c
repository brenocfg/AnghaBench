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
struct gpio_chip {int dummy; } ;
struct bcma_drv_cc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bcma_chipco_gpio_out (struct bcma_drv_cc*,int,int) ; 
 struct bcma_drv_cc* bcma_gpio_get_cc (struct gpio_chip*) ; 

__attribute__((used)) static void bcma_gpio_set_value(struct gpio_chip *chip, unsigned gpio,
				int value)
{
	struct bcma_drv_cc *cc = bcma_gpio_get_cc(chip);

	bcma_chipco_gpio_out(cc, 1 << gpio, value ? 1 << gpio : 0);
}