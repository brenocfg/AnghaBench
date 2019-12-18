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
struct wlp {TYPE_2__* rc; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int __wlp_alloc_device_info (struct wlp*) ; 
 int /*<<< orphan*/  __wlp_fill_device_info (struct wlp*) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 

int __wlp_setup_device_info(struct wlp *wlp)
{
	int result;
	struct device *dev = &wlp->rc->uwb_dev.dev;

	result = __wlp_alloc_device_info(wlp);
	if (result < 0) {
		dev_err(dev, "WLP: Unable to allocate area for "
			"device information.\n");
		return result;
	}
	__wlp_fill_device_info(wlp);
	return 0;
}