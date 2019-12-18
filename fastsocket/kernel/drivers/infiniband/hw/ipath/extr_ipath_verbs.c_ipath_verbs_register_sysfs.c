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
struct ib_device {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ipath_class_attributes ; 

__attribute__((used)) static int ipath_verbs_register_sysfs(struct ib_device *dev)
{
	int i;
	int ret;

	for (i = 0; i < ARRAY_SIZE(ipath_class_attributes); ++i)
		if (device_create_file(&dev->dev,
				       ipath_class_attributes[i])) {
			ret = 1;
			goto bail;
		}

	ret = 0;

bail:
	return ret;
}