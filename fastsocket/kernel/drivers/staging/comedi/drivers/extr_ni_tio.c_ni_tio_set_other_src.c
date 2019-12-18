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
struct ni_gpct_device {scalar_t__ variant; unsigned int* regs; } ;
struct ni_gpct {int /*<<< orphan*/  counter_index; struct ni_gpct_device* counter_dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int NITIO_Gi_ABZ_Reg (int /*<<< orphan*/ ) ; 
#define  NI_GPCT_SOURCE_ENCODER_A 130 
#define  NI_GPCT_SOURCE_ENCODER_B 129 
#define  NI_GPCT_SOURCE_ENCODER_Z 128 
 scalar_t__ ni_gpct_variant_m_series ; 
 int /*<<< orphan*/  write_register (struct ni_gpct*,unsigned int,unsigned int) ; 

__attribute__((used)) static int ni_tio_set_other_src(struct ni_gpct *counter, unsigned index,
				unsigned int source)
{
	struct ni_gpct_device *counter_dev = counter->counter_dev;

	if (counter_dev->variant == ni_gpct_variant_m_series) {
		unsigned int abz_reg, shift, mask;

		abz_reg = NITIO_Gi_ABZ_Reg(counter->counter_index);
		switch (index) {
		case NI_GPCT_SOURCE_ENCODER_A:
			shift = 10;
			break;
		case NI_GPCT_SOURCE_ENCODER_B:
			shift = 5;
			break;
		case NI_GPCT_SOURCE_ENCODER_Z:
			shift = 0;
			break;
		default:
			return -EINVAL;
			break;
		}
		mask = 0x1f << shift;
		if (source > 0x1f) {
			/* Disable gate */
			source = 0x1f;
		}
		counter_dev->regs[abz_reg] &= ~mask;
		counter_dev->regs[abz_reg] |= (source << shift) & mask;
		write_register(counter, counter_dev->regs[abz_reg], abz_reg);
/* printk("%s %x %d %d\n", __func__, counter_dev->regs[abz_reg], index, source); */
		return 0;
	}
	return -EINVAL;
}