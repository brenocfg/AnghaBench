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
 int /*<<< orphan*/  sysfs_hash_and_remove (struct sysfs_dirent*,char const*) ; 
 struct sysfs_dirent sysfs_root ; 

void sysfs_remove_link(struct kobject * kobj, const char * name)
{
	struct sysfs_dirent *parent_sd = NULL;

	if (!kobj)
		parent_sd = &sysfs_root;
	else
		parent_sd = kobj->sd;

	sysfs_hash_and_remove(parent_sd, name);
}