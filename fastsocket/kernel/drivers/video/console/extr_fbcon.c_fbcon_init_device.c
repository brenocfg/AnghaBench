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

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * device_attrs ; 
 int device_create_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fbcon_device ; 
 int fbcon_has_sysfs ; 

__attribute__((used)) static int fbcon_init_device(void)
{
	int i, error = 0;

	fbcon_has_sysfs = 1;

	for (i = 0; i < ARRAY_SIZE(device_attrs); i++) {
		error = device_create_file(fbcon_device, &device_attrs[i]);

		if (error)
			break;
	}

	if (error) {
		while (--i >= 0)
			device_remove_file(fbcon_device, &device_attrs[i]);

		fbcon_has_sysfs = 0;
	}

	return 0;
}