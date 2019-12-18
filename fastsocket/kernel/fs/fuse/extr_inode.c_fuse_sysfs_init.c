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
 void* connections_kobj ; 
 void* fs_kobj ; 
 void* fuse_kobj ; 
 void* kobject_create_and_add (char*,void*) ; 
 int /*<<< orphan*/  kobject_put (void*) ; 

__attribute__((used)) static int fuse_sysfs_init(void)
{
	int err;

	fuse_kobj = kobject_create_and_add("fuse", fs_kobj);
	if (!fuse_kobj) {
		err = -ENOMEM;
		goto out_err;
	}

	connections_kobj = kobject_create_and_add("connections", fuse_kobj);
	if (!connections_kobj) {
		err = -ENOMEM;
		goto out_fuse_unregister;
	}

	return 0;

 out_fuse_unregister:
	kobject_put(fuse_kobj);
 out_err:
	return err;
}