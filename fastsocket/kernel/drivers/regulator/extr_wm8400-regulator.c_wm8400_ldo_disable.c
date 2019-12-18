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
struct wm8400 {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 scalar_t__ WM8400_LDO1_CONTROL ; 
 int /*<<< orphan*/  WM8400_LDO1_ENA ; 
 struct wm8400* rdev_get_drvdata (struct regulator_dev*) ; 
 scalar_t__ rdev_get_id (struct regulator_dev*) ; 
 int wm8400_set_bits (struct wm8400*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm8400_ldo_disable(struct regulator_dev *dev)
{
	struct wm8400 *wm8400 = rdev_get_drvdata(dev);

	return wm8400_set_bits(wm8400, WM8400_LDO1_CONTROL + rdev_get_id(dev),
			       WM8400_LDO1_ENA, 0);
}