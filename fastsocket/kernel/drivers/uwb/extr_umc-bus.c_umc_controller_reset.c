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
struct TYPE_2__ {struct device* parent; } ;
struct umc_dev {TYPE_1__ dev; } ;
struct device {int /*<<< orphan*/  sem; } ;

/* Variables and functions */
 int EAGAIN ; 
 int device_for_each_child (struct device*,struct device*,int /*<<< orphan*/ ) ; 
 scalar_t__ down_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  umc_bus_post_reset_helper ; 
 int /*<<< orphan*/  umc_bus_pre_reset_helper ; 
 int /*<<< orphan*/  up (int /*<<< orphan*/ *) ; 

int umc_controller_reset(struct umc_dev *umc)
{
	struct device *parent = umc->dev.parent;
	int ret = 0;

	if(down_trylock(&parent->sem))
		return -EAGAIN;
	ret = device_for_each_child(parent, parent, umc_bus_pre_reset_helper);
	if (ret >= 0)
		ret = device_for_each_child(parent, parent, umc_bus_post_reset_helper);
	up(&parent->sem);

	return ret;
}