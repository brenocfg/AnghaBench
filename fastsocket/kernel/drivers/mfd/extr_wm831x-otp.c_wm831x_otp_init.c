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
struct wm831x {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_attr_unique_id ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int wm831x_otp_init(struct wm831x *wm831x)
{
	int ret;

	ret = device_create_file(wm831x->dev, &dev_attr_unique_id);
	if (ret != 0)
		dev_err(wm831x->dev, "Unique ID attribute not created: %d\n",
			ret);

	return ret;
}