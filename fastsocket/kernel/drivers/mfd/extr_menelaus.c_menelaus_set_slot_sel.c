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
 int /*<<< orphan*/  MENELAUS_GPIO_CTRL ; 
 int menelaus_read_reg (int /*<<< orphan*/ ) ; 
 int menelaus_write_reg (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_1__* the_menelaus ; 

int menelaus_set_slot_sel(int enable)
{
	int ret;

	mutex_lock(&the_menelaus->lock);
	ret = menelaus_read_reg(MENELAUS_GPIO_CTRL);
	if (ret < 0)
		goto out;
	ret |= 0x02;
	if (enable)
		ret |= 1 << 5;
	else
		ret &= ~(1 << 5);
	ret = menelaus_write_reg(MENELAUS_GPIO_CTRL, ret);
out:
	mutex_unlock(&the_menelaus->lock);
	return ret;
}