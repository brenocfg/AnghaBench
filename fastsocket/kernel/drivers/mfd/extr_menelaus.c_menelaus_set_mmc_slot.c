#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  MENELAUS_MCT_CTRL2 ; 
 int /*<<< orphan*/  MENELAUS_MCT_CTRL3 ; 
 int menelaus_read_reg (int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 

int menelaus_set_mmc_slot(int slot, int enable, int power, int cd_en)
{
	int ret, val;

	if (slot != 1 && slot != 2)
		return -EINVAL;
	if (power >= 3)
		return -EINVAL;

	mutex_lock(&the_menelaus->lock);

	ret = menelaus_read_reg(MENELAUS_MCT_CTRL2);
	if (ret < 0)
		goto out;
	val = ret;
	if (slot == 1) {
		if (cd_en)
			val |= (1 << 4) | (1 << 6);
		else
			val &= ~((1 << 4) | (1 << 6));
	} else {
		if (cd_en)
			val |= (1 << 5) | (1 << 7);
		else
			val &= ~((1 << 5) | (1 << 7));
	}
	ret = menelaus_write_reg(MENELAUS_MCT_CTRL2, val);
	if (ret < 0)
		goto out;

	ret = menelaus_read_reg(MENELAUS_MCT_CTRL3);
	if (ret < 0)
		goto out;
	val = ret;
	if (slot == 1) {
		if (enable)
			val |= 1 << 0;
		else
			val &= ~(1 << 0);
	} else {
		int b;

		if (enable)
			ret |= 1 << 1;
		else
			ret &= ~(1 << 1);
		b = menelaus_read_reg(MENELAUS_MCT_CTRL2);
		b &= ~0x03;
		b |= power;
		ret = menelaus_write_reg(MENELAUS_MCT_CTRL2, b);
		if (ret < 0)
			goto out;
	}
	/* Disable autonomous shutdown */
	val &= ~(0x03 << 2);
	ret = menelaus_write_reg(MENELAUS_MCT_CTRL3, val);
out:
	mutex_unlock(&the_menelaus->lock);
	return ret;
}