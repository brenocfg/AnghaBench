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
struct sysfs_dirent {int dummy; } ;
struct kobject {int dummy; } ;
struct attribute_group {struct attribute** attrs; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  sysfs_hash_and_remove (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void remove_files(struct sysfs_dirent *dir_sd, struct kobject *kobj,
			 const struct attribute_group *grp)
{
	struct attribute *const* attr;
	int i;

	for (i = 0, attr = grp->attrs; *attr; i++, attr++)
		sysfs_hash_and_remove(dir_sd, (*attr)->name);
}