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
struct pinmux_cfg_reg {int field_width; int /*<<< orphan*/  reg_width; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 unsigned long gpio_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned long) ; 

__attribute__((used)) static int check_config_reg(struct pinmux_info *gpioc,
			    struct pinmux_cfg_reg *crp,
			    int index)
{
	unsigned long ncomb, pos, value;

	ncomb = 1 << crp->field_width;
	pos = index / ncomb;
	value = index % ncomb;

	if (gpio_read_reg(crp->reg, crp->reg_width,
			  crp->field_width, pos) == value)
		return 0;

	return -1;
}