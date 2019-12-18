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
struct vx_core {int dummy; } ;

/* Variables and functions */
 unsigned int VX_CNTRL_REGISTER_VALUE ; 
 unsigned int VX_USERBIT0_MASK ; 
 unsigned int VX_USERBIT1_MASK ; 
 int /*<<< orphan*/  udelay (int) ; 
 int /*<<< orphan*/  vx2_inl (struct vx_core*,unsigned int) ; 
 int /*<<< orphan*/  vx2_outl (struct vx_core*,unsigned int,unsigned int) ; 

__attribute__((used)) static int put_xilinx_data(struct vx_core *chip, unsigned int port, unsigned int counts, unsigned char data)
{
	unsigned int i;

	for (i = 0; i < counts; i++) {
		unsigned int val;

		/* set the clock bit to 0. */
		val = VX_CNTRL_REGISTER_VALUE & ~VX_USERBIT0_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);
		udelay(1);

		if (data & (1 << i))
			val |= VX_USERBIT1_MASK;
		else
			val &= ~VX_USERBIT1_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);

		/* set the clock bit to 1. */
		val |= VX_USERBIT0_MASK;
		vx2_outl(chip, port, val);
		vx2_inl(chip, port);
		udelay(1);
	}
	return 0;
}