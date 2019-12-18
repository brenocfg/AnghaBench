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
struct device {int /*<<< orphan*/  kobj; } ;

/* Variables and functions */
 int /*<<< orphan*/  pccard_cis_attr ; 
 int /*<<< orphan*/  socket_attrs ; 
 int sysfs_create_bin_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int sysfs_create_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_remove_group (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int pccard_sysfs_add_socket(struct device *dev)
{
	int ret = 0;

	ret = sysfs_create_group(&dev->kobj, &socket_attrs);
	if (!ret) {
		ret = sysfs_create_bin_file(&dev->kobj, &pccard_cis_attr);
		if (ret)
			sysfs_remove_group(&dev->kobj, &socket_attrs);
	}
	return ret;
}