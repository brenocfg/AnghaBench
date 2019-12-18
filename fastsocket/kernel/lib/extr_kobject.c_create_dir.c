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
struct kobject {int dummy; } ;

/* Variables and functions */
 scalar_t__ kobject_name (struct kobject*) ; 
 int populate_dir (struct kobject*) ; 
 int sysfs_create_dir (struct kobject*) ; 
 int /*<<< orphan*/  sysfs_remove_dir (struct kobject*) ; 

__attribute__((used)) static int create_dir(struct kobject *kobj)
{
	int error = 0;
	if (kobject_name(kobj)) {
		error = sysfs_create_dir(kobj);
		if (!error) {
			error = populate_dir(kobj);
			if (error)
				sysfs_remove_dir(kobj);
		}
	}
	return error;
}