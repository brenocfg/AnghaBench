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
struct sys_device {int /*<<< orphan*/ * cls; scalar_t__ id; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cmm_attrs ; 
 int /*<<< orphan*/  cmm_sysdev_class ; 
 int sysdev_class_register (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysdev_class_unregister (int /*<<< orphan*/ *) ; 
 int sysdev_create_file (struct sys_device*,int /*<<< orphan*/ ) ; 
 int sysdev_register (struct sys_device*) ; 
 int /*<<< orphan*/  sysdev_remove_file (struct sys_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysdev_unregister (struct sys_device*) ; 

__attribute__((used)) static int cmm_sysfs_register(struct sys_device *sysdev)
{
	int i, rc;

	if ((rc = sysdev_class_register(&cmm_sysdev_class)))
		return rc;

	sysdev->id = 0;
	sysdev->cls = &cmm_sysdev_class;

	if ((rc = sysdev_register(sysdev)))
		goto class_unregister;

	for (i = 0; i < ARRAY_SIZE(cmm_attrs); i++) {
		if ((rc = sysdev_create_file(sysdev, cmm_attrs[i])))
			goto fail;
	}

	return 0;

fail:
	while (--i >= 0)
		sysdev_remove_file(sysdev, cmm_attrs[i]);
	sysdev_unregister(sysdev);
class_unregister:
	sysdev_class_unregister(&cmm_sysdev_class);
	return rc;
}