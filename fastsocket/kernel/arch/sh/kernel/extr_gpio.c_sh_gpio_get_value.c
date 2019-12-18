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
struct pinmux_info {int dummy; } ;
struct pinmux_data_reg {int /*<<< orphan*/  reg_width; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ get_data_reg (struct pinmux_info*,unsigned int,struct pinmux_data_reg**,int*) ; 
 int gpio_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int sh_gpio_get_value(struct pinmux_info *gpioc, unsigned gpio)
{
	struct pinmux_data_reg *dr = NULL;
	int bit = 0;

	if (!gpioc || get_data_reg(gpioc, gpio, &dr, &bit) != 0) {
		BUG();
		return 0;
	}

	return gpio_read_reg(dr->reg, dr->reg_width, 1, bit);
}