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
 int ENOMEM ; 
 int /*<<< orphan*/  fs_kobj ; 
 int /*<<< orphan*/  kobject_create_and_add (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ ) ; 
 scalar_t__ sysfs_create_group (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  v9fs_attr_group ; 
 int /*<<< orphan*/  v9fs_kobj ; 

__attribute__((used)) static int v9fs_sysfs_init(void)
{
	v9fs_kobj = kobject_create_and_add("9p", fs_kobj);
	if (!v9fs_kobj)
		return -ENOMEM;

	if (sysfs_create_group(v9fs_kobj, &v9fs_attr_group)) {
		kobject_put(v9fs_kobj);
		return -ENOMEM;
	}

	return 0;
}