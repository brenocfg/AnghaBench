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
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; struct bin_buffer* private_data; } ;
struct bin_buffer {TYPE_1__* vm_ops; } ;
struct TYPE_5__ {struct sysfs_dirent* d_fsdata; } ;
struct TYPE_4__ {int (* access ) (struct vm_area_struct*,unsigned long,void*,int,int) ;} ;

/* Variables and functions */
 int EINVAL ; 
 int stub1 (struct vm_area_struct*,unsigned long,void*,int,int) ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int bin_access(struct vm_area_struct *vma, unsigned long addr,
		  void *buf, int len, int write)
{
	struct file *file = vma->vm_file;
	struct bin_buffer *bb = file->private_data;
	struct sysfs_dirent *attr_sd = file->f_path.dentry->d_fsdata;
	int ret;

	if (!bb->vm_ops || !bb->vm_ops->access)
		return -EINVAL;

	if (!sysfs_get_active_two(attr_sd))
		return -EINVAL;

	ret = bb->vm_ops->access(vma, addr, buf, len, write);

	sysfs_put_active_two(attr_sd);
	return ret;
}