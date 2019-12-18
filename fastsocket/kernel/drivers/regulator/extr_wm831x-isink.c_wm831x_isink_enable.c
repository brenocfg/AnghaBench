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
 int /*<<< orphan*/  WM831X_CS1_DRIVE ; 
 int /*<<< orphan*/  WM831X_CS1_ENA ; 
 struct wm831x_isink* rdev_get_drvdata (struct regulator_dev*) ; 
 int wm831x_set_bits (struct wm831x*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm831x_isink_enable(struct regulator_dev *rdev)
{
	struct wm831x_isink *isink = rdev_get_drvdata(rdev);
	struct wm831x *wm831x = isink->wm831x;
	int ret;

	/* We have a two stage enable: first start the ISINK... */
	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_ENA,
			      WM831X_CS1_ENA);
	if (ret != 0)
		return ret;

	/* ...then enable drive */
	ret = wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_DRIVE,
			      WM831X_CS1_DRIVE);
	if (ret != 0)
		wm831x_set_bits(wm831x, isink->reg, WM831X_CS1_ENA, 0);

	return ret;

}