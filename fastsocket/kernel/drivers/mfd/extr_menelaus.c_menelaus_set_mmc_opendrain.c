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
 int /*<<< orphan*/  MENELAUS_MCT_CTRL1 ; 
 int menelaus_read_reg (int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 

int menelaus_set_mmc_opendrain(int slot, int enable)
{
	int ret, val;

	if (slot != 1 && slot != 2)
		return -EINVAL;
	mutex_lock(&the_menelaus->lock);
	ret = menelaus_read_reg(MENELAUS_MCT_CTRL1);
	if (ret < 0) {
		mutex_unlock(&the_menelaus->lock);
		return ret;
	}
	val = ret;
	if (slot == 1) {
		if (enable)
			val |= 1 << 2;
		else
			val &= ~(1 << 2);
	} else {
		if (enable)
			val |= 1 << 3;
		else
			val &= ~(1 << 3);
	}
	ret = menelaus_write_reg(MENELAUS_MCT_CTRL1, val);
	mutex_unlock(&the_menelaus->lock);

	return ret;
}