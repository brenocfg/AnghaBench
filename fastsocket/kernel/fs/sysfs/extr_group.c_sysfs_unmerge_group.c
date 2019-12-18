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
struct kobject {int /*<<< orphan*/  sd; } ;
struct attribute_group {struct attribute** attrs; int /*<<< orphan*/  name; } ;
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct sysfs_dirent* sysfs_get (int /*<<< orphan*/ ) ; 
 struct sysfs_dirent* sysfs_get_dirent (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_hash_and_remove (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 

void sysfs_unmerge_group(struct kobject *kobj,
		       const struct attribute_group *grp)
{
	struct sysfs_dirent *dir_sd;
	struct attribute *const *attr;

	if (grp)
		dir_sd = sysfs_get_dirent(kobj->sd, grp->name);
	else
		dir_sd = sysfs_get(kobj->sd);
	if (dir_sd) {
		for (attr = grp->attrs; *attr; ++attr)
			sysfs_hash_and_remove(dir_sd, (*attr)->name);
		sysfs_put(dir_sd);
	}
}