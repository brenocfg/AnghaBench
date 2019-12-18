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
struct pinmux_data_reg {unsigned long reg_width; int /*<<< orphan*/  reg_shadow; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  clear_bit (unsigned long,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gpio_write_raw_reg (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_info (char*,int /*<<< orphan*/ ,int,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  set_bit (unsigned long,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void gpio_write_bit(struct pinmux_data_reg *dr,
			   unsigned long in_pos, unsigned long value)
{
	unsigned long pos;

	pos = dr->reg_width - (in_pos + 1);

#ifdef DEBUG
	pr_info("write_bit addr = %lx, value = %ld, pos = %ld, "
		"r_width = %ld\n",
		dr->reg, !!value, pos, dr->reg_width);
#endif

	if (value)
		set_bit(pos, &dr->reg_shadow);
	else
		clear_bit(pos, &dr->reg_shadow);

	gpio_write_raw_reg(dr->reg, dr->reg_width, dr->reg_shadow);
}