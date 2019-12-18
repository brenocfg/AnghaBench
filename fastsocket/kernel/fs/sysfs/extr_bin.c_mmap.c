#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vm_area_struct {scalar_t__ vm_ops; struct file* vm_file; } ;
struct TYPE_8__ {struct bin_attribute* bin_attr; } ;
struct sysfs_dirent {TYPE_5__* s_parent; TYPE_3__ s_bin_attr; } ;
struct kobject {int dummy; } ;
struct TYPE_7__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; struct bin_buffer* private_data; } ;
struct bin_buffer {int mmapped; scalar_t__ vm_ops; int /*<<< orphan*/  mutex; } ;
struct bin_attribute {int (* mmap ) (struct file*,struct kobject*,struct bin_attribute*,struct vm_area_struct*) ;} ;
struct TYPE_9__ {struct kobject* kobj; } ;
struct TYPE_10__ {TYPE_4__ s_dir; } ;
struct TYPE_6__ {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENODEV ; 
 int /*<<< orphan*/  bin_vm_ops ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int stub1 (struct file*,struct kobject*,struct bin_attribute*,struct vm_area_struct*) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int mmap(struct file *file, struct vm_area_struct *vma)
{
	struct bin_buffer *bb = file->private_data;
	struct sysfs_dirent *attr_sd = file->f_path.dentry->d_fsdata;
	struct bin_attribute *attr = attr_sd->s_bin_attr.bin_attr;
	struct kobject *kobj = attr_sd->s_parent->s_dir.kobj;
	int rc;

	mutex_lock(&bb->mutex);

	/* need attr_sd for attr, its parent for kobj */
	rc = -ENODEV;
	if (!sysfs_get_active_two(attr_sd))
		goto out_unlock;

	rc = -EINVAL;
	if (!attr->mmap)
		goto out_put;

	rc = attr->mmap(file, kobj, attr, vma);
	if (rc)
		goto out_put;

	/*
	 * PowerPC's pci_mmap of legacy_mem uses shmem_zero_setup()
	 * to satisfy versions of X which crash if the mmap fails: that
	 * substitutes a new vm_file, and we don't then want bin_vm_ops.
	 */
	if (vma->vm_file != file)
		goto out_put;

	rc = -EINVAL;
	if (bb->mmapped && bb->vm_ops != vma->vm_ops)
		goto out_put;

	rc = 0;
	bb->mmapped = 1;
	bb->vm_ops = vma->vm_ops;
	vma->vm_ops = &bin_vm_ops;
out_put:
	sysfs_put_active_two(attr_sd);
out_unlock:
	mutex_unlock(&bb->mutex);

	return rc;
}