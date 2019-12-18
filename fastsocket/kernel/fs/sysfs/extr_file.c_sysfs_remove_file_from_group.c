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
struct attribute {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct sysfs_dirent* sysfs_get (int /*<<< orphan*/ ) ; 
 struct sysfs_dirent* sysfs_get_dirent (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  sysfs_hash_and_remove (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 

void sysfs_remove_file_from_group(struct kobject *kobj,
		const struct attribute *attr, const char *group)
{
	struct sysfs_dirent *dir_sd;

	if (group)
		dir_sd = sysfs_get_dirent(kobj->sd, group);
	else
		dir_sd = sysfs_get(kobj->sd);
	if (dir_sd) {
		sysfs_hash_and_remove(dir_sd, attr->name);
		sysfs_put(dir_sd);
	}
}