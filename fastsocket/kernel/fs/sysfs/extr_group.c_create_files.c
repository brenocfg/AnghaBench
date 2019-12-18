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
struct attribute_group {int (* is_visible ) (struct kobject*,struct attribute* const,int) ;struct attribute** attrs; } ;
struct attribute {int mode; int /*<<< orphan*/  name; } ;
typedef  int mode_t ;

/* Variables and functions */
 int /*<<< orphan*/  SYSFS_KOBJ_ATTR ; 
 int /*<<< orphan*/  remove_files (struct sysfs_dirent*,struct kobject*,struct attribute_group const*) ; 
 int stub1 (struct kobject*,struct attribute* const,int) ; 
 int sysfs_add_file_mode (struct sysfs_dirent*,struct attribute* const,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sysfs_hash_and_remove (struct sysfs_dirent*,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int create_files(struct sysfs_dirent *dir_sd, struct kobject *kobj,
			const struct attribute_group *grp, int update)
{
	struct attribute *const* attr;
	int error = 0, i;

	for (i = 0, attr = grp->attrs; *attr && !error; i++, attr++) {
		mode_t mode = 0;

		/* in update mode, we're changing the permissions or
		 * visibility.  Do this by first removing then
		 * re-adding (if required) the file */
		if (update)
			sysfs_hash_and_remove(dir_sd, (*attr)->name);
		if (grp->is_visible) {
			mode = grp->is_visible(kobj, *attr, i);
			if (!mode)
				continue;
		}
		error = sysfs_add_file_mode(dir_sd, *attr, SYSFS_KOBJ_ATTR,
					    (*attr)->mode | mode);
		if (unlikely(error))
			break;
	}
	if (error)
		remove_files(dir_sd, kobj, grp);
	return error;
}