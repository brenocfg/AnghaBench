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
struct pcf50633 {int* mask_regs; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int PCF50633_REG_INT1M ; 
 int __pcf50633_read (struct pcf50633*,int,int,int*) ; 
 int __pcf50633_write (struct pcf50633*,int,int,int*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int __pcf50633_irq_mask_set(struct pcf50633 *pcf, int irq, u8 mask)
{
	u8 reg, bits, tmp;
	int ret = 0, idx;

	idx = irq >> 3;
	reg =  PCF50633_REG_INT1M + idx;
	bits = 1 << (irq & 0x07);

	mutex_lock(&pcf->lock);

	if (mask) {
		ret = __pcf50633_read(pcf, reg, 1, &tmp);
		if (ret < 0)
			goto out;

		tmp |= bits;

		ret = __pcf50633_write(pcf, reg, 1, &tmp);
		if (ret < 0)
			goto out;

		pcf->mask_regs[idx] &= ~bits;
		pcf->mask_regs[idx] |= bits;
	} else {
		ret = __pcf50633_read(pcf, reg, 1, &tmp);
		if (ret < 0)
			goto out;

		tmp &= ~bits;

		ret = __pcf50633_write(pcf, reg, 1, &tmp);
		if (ret < 0)
			goto out;

		pcf->mask_regs[idx] &= ~bits;
	}
out:
	mutex_unlock(&pcf->lock);

	return ret;
}