#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sysfs_ops {int (* store ) (struct kobject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ;} ;
struct TYPE_6__ {int /*<<< orphan*/  attr; } ;
struct sysfs_dirent {TYPE_3__ s_attr; TYPE_2__* s_parent; } ;
struct sysfs_buffer {int /*<<< orphan*/  page; struct sysfs_ops* ops; } ;
struct kobject {int dummy; } ;
struct dentry {struct sysfs_dirent* d_fsdata; } ;
struct TYPE_4__ {struct kobject* kobj; } ;
struct TYPE_5__ {TYPE_1__ s_dir; } ;

/* Variables and functions */
 int ENODEV ; 
 int stub1 (struct kobject*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int
flush_write_buffer(struct dentry * dentry, struct sysfs_buffer * buffer, size_t count)
{
	struct sysfs_dirent *attr_sd = dentry->d_fsdata;
	struct kobject *kobj = attr_sd->s_parent->s_dir.kobj;
	const struct sysfs_ops * ops = buffer->ops;
	int rc;

	/* need attr_sd for attr and ops, its parent for kobj */
	if (!sysfs_get_active_two(attr_sd))
		return -ENODEV;

	rc = ops->store(kobj, attr_sd->s_attr.attr, buffer->page, count);

	sysfs_put_active_two(attr_sd);

	return rc;
}