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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sysfs_dirent* sysfs_find_dirent (struct sysfs_dirent*,unsigned char const*) ; 
 int /*<<< orphan*/  sysfs_get (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_mutex ; 

struct sysfs_dirent *sysfs_get_dirent(struct sysfs_dirent *parent_sd,
				      const unsigned char *name)
{
	struct sysfs_dirent *sd;

	mutex_lock(&sysfs_mutex);
	sd = sysfs_find_dirent(parent_sd, name);
	sysfs_get(sd);
	mutex_unlock(&sysfs_mutex);

	return sd;
}