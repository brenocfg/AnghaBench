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
struct sysfs_addrm_cxt {int dummy; } ;

/* Variables and functions */
 int ENOENT ; 
 int /*<<< orphan*/  sysfs_addrm_finish (struct sysfs_addrm_cxt*) ; 
 int /*<<< orphan*/  sysfs_addrm_start (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_find_dirent (struct sysfs_dirent*,char const*) ; 
 int /*<<< orphan*/  sysfs_remove_one (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 

int sysfs_hash_and_remove(struct sysfs_dirent *dir_sd, const char *name)
{
	struct sysfs_addrm_cxt acxt;
	struct sysfs_dirent *sd;

	if (!dir_sd)
		return -ENOENT;

	sysfs_addrm_start(&acxt, dir_sd);

	sd = sysfs_find_dirent(dir_sd, name);
	if (sd)
		sysfs_remove_one(&acxt, sd);

	sysfs_addrm_finish(&acxt);

	if (sd)
		return 0;
	else
		return -ENOENT;
}