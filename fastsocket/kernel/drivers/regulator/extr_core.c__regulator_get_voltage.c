#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct regulator_dev {TYPE_2__* desc; } ;
struct TYPE_4__ {TYPE_1__* ops; } ;
struct TYPE_3__ {int (* get_voltage ) (struct regulator_dev*) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct regulator_dev*) ; 

__attribute__((used)) static int _regulator_get_voltage(struct regulator_dev *rdev)
{
	/* sanity check */
	if (rdev->desc->ops->get_voltage)
		return rdev->desc->ops->get_voltage(rdev);
	else
		return -EINVAL;
}