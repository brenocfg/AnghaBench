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
struct wm831x_isink {int /*<<< orphan*/  reg; struct wm831x* wm831x; } ;
struct wm831x {int dummy; } ;
struct regulator_dev {int dummy; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  WM831X_CS1_ISEL_MASK ; 
 struct wm831x_isink* rdev_get_drvdata (struct regulator_dev*) ; 
 int* wm831x_isinkv_values ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int wm831x_isink_set_current(struct regulator_dev *rdev,
				    int min_uA, int max_uA)
{
	struct wm831x_isink *isink = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = isink->wm831x;
	int ret, i;

	for (i = 0; i < ARRAY_SIZE(wm831x_isinkv_values); i++) {
		int val = wm831x_isinkv_values[i];
		if (min_uA >= val && val <= max_uA) {
			ret = wm831x_set_bits(wm831x, isink->reg,
					      WM831X_CS1_ISEL_MASK, i);
			return ret;
		}
	}

	return -EINVAL;
}