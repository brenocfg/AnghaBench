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
struct kobject {struct sysfs_dirent* sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sysfs_dirent* sysfs_find_dirent (struct sysfs_dirent*,char const*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 
 int /*<<< orphan*/  sysfs_notify_dirent (struct sysfs_dirent*) ; 

void sysfs_notify(struct kobject *k, const char *dir, const char *attr)
{
	struct sysfs_dirent *sd = k->sd;

	mutex_lock(&sysfs_mutex);

	if (sd && dir)
		sd = sysfs_find_dirent(sd, dir);
	if (sd && attr)
		sd = sysfs_find_dirent(sd, attr);
	if (sd)
		sysfs_notify_dirent(sd);

	mutex_unlock(&sysfs_mutex);
}