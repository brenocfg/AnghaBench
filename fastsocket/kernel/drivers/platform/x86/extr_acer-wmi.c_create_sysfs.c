#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACER_CAP_THREEG ; 
 int ENOMEM ; 
 TYPE_1__* acer_platform_device ; 
 int /*<<< orphan*/  dev_attr_interface ; 
 int /*<<< orphan*/  dev_attr_threeg ; 
 int device_create_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ has_cap (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_sysfs (TYPE_1__*) ; 

__attribute__((used)) static int create_sysfs(void)
{
	int retval = -ENOMEM;

	if (has_cap(ACER_CAP_THREEG)) {
		retval = device_create_file(&acer_platform_device->dev,
			&dev_attr_threeg);
		if (retval)
			goto error_sysfs;
	}

	retval = device_create_file(&acer_platform_device->dev,
		&dev_attr_interface);
	if (retval)
		goto error_sysfs;

	return 0;

error_sysfs:
		remove_sysfs(acer_platform_device);
	return retval;
}