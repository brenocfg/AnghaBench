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
 int /*<<< orphan*/  BUG () ; 
 unsigned long ctrl_inb (unsigned long) ; 
 unsigned long ctrl_inl (unsigned long) ; 
 unsigned long ctrl_inw (unsigned long) ; 

__attribute__((used)) static unsigned long gpio_read_raw_reg(unsigned long reg,
				       unsigned long reg_width)
{
	switch (reg_width) {
	case 8:
		return ctrl_inb(reg);
	case 16:
		return ctrl_inw(reg);
	case 32:
		return ctrl_inl(reg);
	}

	BUG();
	return 0;
}