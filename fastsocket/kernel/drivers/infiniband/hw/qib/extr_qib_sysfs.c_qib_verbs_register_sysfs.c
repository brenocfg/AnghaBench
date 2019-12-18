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
struct ib_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {struct ib_device ibdev; } ;
struct qib_devdata {TYPE_1__ verbs_dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * qib_attributes ; 

int qib_verbs_register_sysfs(struct qib_devdata *dd)
{
	struct ib_device *dev = &dd->verbs_dev.ibdev;
	int i, ret;

	for (i = 0; i < ARRAY_SIZE(qib_attributes); ++i) {
		ret = device_create_file(&dev->dev, qib_attributes[i]);
		if (ret)
			return ret;
	}

	return 0;
}