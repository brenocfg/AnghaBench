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
struct TYPE_2__ {struct kobject* kobj; } ;
struct sysfs_dirent {TYPE_1__ s_dir; } ;
struct sysfs_addrm_cxt {int dummy; } ;
struct kobject {int dummy; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  SYSFS_DIR ; 
 int S_IFDIR ; 
 int S_IRUGO ; 
 int S_IRWXU ; 
 int S_IXUGO ; 
 int sysfs_add_one (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_addrm_finish (struct sysfs_addrm_cxt*) ; 
 int /*<<< orphan*/  sysfs_addrm_start (struct sysfs_addrm_cxt*,struct sysfs_dirent*) ; 
 struct sysfs_dirent* sysfs_new_dirent (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysfs_put (struct sysfs_dirent*) ; 

__attribute__((used)) static int create_dir(struct kobject *kobj, struct sysfs_dirent *parent_sd,
		      const char *name, struct sysfs_dirent **p_sd)
{
	umode_t mode = S_IFDIR| S_IRWXU | S_IRUGO | S_IXUGO;
	struct sysfs_addrm_cxt acxt;
	struct sysfs_dirent *sd;
	int rc;

	/* allocate */
	sd = sysfs_new_dirent(name, mode, SYSFS_DIR);
	if (!sd)
		return -ENOMEM;
	sd->s_dir.kobj = kobj;

	/* link in */
	sysfs_addrm_start(&acxt, parent_sd);
	rc = sysfs_add_one(&acxt, sd);
	sysfs_addrm_finish(&acxt);

	if (rc == 0)
		*p_sd = sd;
	else
		sysfs_put(sd);

	return rc;
}