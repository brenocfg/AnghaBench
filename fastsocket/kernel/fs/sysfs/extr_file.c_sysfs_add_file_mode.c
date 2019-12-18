#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int umode_t ;
struct TYPE_2__ {void* attr; } ;
struct sysfs_dirent {TYPE_1__ s_attr; } ;
struct sysfs_addrm_cxt {int dummy; } ;
struct attribute {int /*<<< orphan*/  name; } ;
typedef  int mode_t ;

/* Variables and functions */
 int ENOMEM ; 
 int S_IALLUGO ; 
 int S_IFREG ; 
 int sysfs_add_one (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_addrm_finish (struct sysfs_addrm_cxt*) ; 
 int /*<<< orphan*/  sysfs_addrm_start (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_new_dirent (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 

int sysfs_add_file_mode(struct sysfs_dirent *dir_sd,
			const struct attribute *attr, int type, mode_t amode)
{
	umode_t mode = (amode & S_IALLUGO) | S_IFREG;
	struct sysfs_addrm_cxt acxt;
	struct sysfs_dirent *sd;
	int rc;

	sd = sysfs_new_dirent(attr->name, mode, type);
	if (!sd)
		return -ENOMEM;
	sd->s_attr.attr = (void *)attr;

	sysfs_addrm_start(&acxt, dir_sd);
	rc = sysfs_add_one(&acxt, sd);
	sysfs_addrm_finish(&acxt);

	if (rc)
		sysfs_put(sd);

	return rc;
}