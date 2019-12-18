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
struct regulator_dev {int dummy; } ;
struct bq24022_mach_info {int /*<<< orphan*/  gpio_nce; } ;

/* Variables and functions */
 int /*<<< orphan*/  gpio_get_value (int /*<<< orphan*/ ) ; 
 struct bq24022_mach_info* rdev_get_drvdata (struct regulator_dev*) ; 

__attribute__((used)) static int bq24022_is_enabled(struct regulator_dev *rdev)
{
	struct bq24022_mach_info *pdata = rdev_get_drvdata(rdev);

	return !gpio_get_value(pdata->gpio_nce);
}