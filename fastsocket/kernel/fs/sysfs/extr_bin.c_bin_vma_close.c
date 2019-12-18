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
struct vm_area_struct {struct file* vm_file; } ;
struct sysfs_dirent {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {TYPE_2__ f_path; struct bin_buffer* private_data; } ;
struct bin_buffer {TYPE_3__* vm_ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (struct vm_area_struct*) ;} ;
struct TYPE_4__ {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (struct vm_area_struct*) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static void bin_vma_close(struct vm_area_struct *vma)
{
	struct file *file = vma->vm_file;
	struct bin_buffer *bb = file->private_data;
	struct sysfs_dirent *attr_sd = file->f_path.dentry->d_fsdata;

	if (!bb->vm_ops || !bb->vm_ops->close)
		return;

	if (!sysfs_get_active_two(attr_sd))
		return;

	bb->vm_ops->close(vma);

	sysfs_put_active_two(attr_sd);
}