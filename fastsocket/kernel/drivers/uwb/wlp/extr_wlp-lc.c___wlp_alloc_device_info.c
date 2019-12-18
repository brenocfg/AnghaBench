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
struct wlp_device_info {int dummy; } ;
struct wlp {int /*<<< orphan*/ * dev_info; TYPE_2__* rc; } ;
struct device {int dummy; } ;
struct TYPE_3__ {struct device dev; } ;
struct TYPE_4__ {TYPE_1__ uwb_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_err (struct device*,char*) ; 
 int /*<<< orphan*/ * kzalloc (int,int /*<<< orphan*/ ) ; 

int __wlp_alloc_device_info(struct wlp *wlp)
{
	struct device *dev = &wlp->rc->uwb_dev.dev;
	BUG_ON(wlp->dev_info != NULL);
	wlp->dev_info = kzalloc(sizeof(struct wlp_device_info), GFP_KERNEL);
	if (wlp->dev_info == NULL) {
		dev_err(dev, "WLP: Unable to allocate memory for "
			"device information.\n");
		return -ENOMEM;
	}
	return 0;
}