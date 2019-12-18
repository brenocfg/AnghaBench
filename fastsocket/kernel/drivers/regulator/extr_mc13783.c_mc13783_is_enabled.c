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
struct regulator_dev {int dummy; } ;
struct mc13783_priv {int /*<<< orphan*/  mc13783; } ;
struct TYPE_2__ {unsigned int enable_bit; int /*<<< orphan*/  reg; } ;

/* Variables and functions */
 int mc13783_reg_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 TYPE_1__* mc13783_regulators ; 
 struct mc13783_priv* rdev_get_drvdata (struct regulator_dev*) ; 
 int rdev_get_id (struct regulator_dev*) ; 

__attribute__((used)) static int mc13783_is_enabled(struct regulator_dev *rdev)
{
	struct mc13783_priv *priv = rdev_get_drvdata(rdev);
	int ret, id = rdev_get_id(rdev);
	unsigned int val;

	ret = mc13783_reg_read(priv->mc13783, mc13783_regulators[id].reg, &val);
	if (ret)
		return ret;

	return (val & mc13783_regulators[id].enable_bit) != 0;
}