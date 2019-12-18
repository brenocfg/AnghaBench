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
struct vm_fault {int dummy; } ;
struct vm_area_struct {struct file* vm_file; } ;
struct sysfs_dirent {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; struct bin_buffer* private_data; } ;
struct bin_buffer {TYPE_3__* vm_ops; } ;
struct TYPE_6__ {int (* page_mkwrite ) (struct vm_area_struct*,struct vm_fault*) ;} ;
struct TYPE_4__ {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int VM_FAULT_SIGBUS ; 
 int /*<<< orphan*/  file_update_time (struct file*) ; 
 int stub1 (struct vm_area_struct*,struct vm_fault*) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int bin_page_mkwrite(struct vm_area_struct *vma, struct vm_fault *vmf)
{
	struct file *file = vma->vm_file;
	struct bin_buffer *bb = file->private_data;
	struct sysfs_dirent *attr_sd = file->f_path.dentry->d_fsdata;
	int ret;

	if (!bb->vm_ops)
		return VM_FAULT_SIGBUS;

	if (!bb->vm_ops->page_mkwrite) {
		file_update_time(file);
		return 0;
	}

	if (!sysfs_get_active_two(attr_sd))
		return VM_FAULT_SIGBUS;

	ret = bb->vm_ops->page_mkwrite(vma, vmf);

	sysfs_put_active_two(attr_sd);
	return ret;
}