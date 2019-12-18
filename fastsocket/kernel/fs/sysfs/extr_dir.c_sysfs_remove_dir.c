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
 int /*<<< orphan*/  __sysfs_remove_dir (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_assoc_lock ; 

void sysfs_remove_dir(struct kobject * kobj)
{
	struct sysfs_dirent *sd = kobj->sd;

	spin_lock(&sysfs_assoc_lock);
	kobj->sd = NULL;
	spin_unlock(&sysfs_assoc_lock);

	__sysfs_remove_dir(sd);
}