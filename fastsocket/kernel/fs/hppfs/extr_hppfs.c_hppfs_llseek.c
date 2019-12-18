#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct hppfs_private {struct file* proc_file; } ;
struct TYPE_8__ {TYPE_3__* dentry; } ;
struct file {TYPE_4__ f_path; struct hppfs_private* private_data; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_7__ {TYPE_2__* d_inode; } ;
struct TYPE_6__ {TYPE_1__* i_fop; } ;
struct TYPE_5__ {scalar_t__ (* llseek ) (struct file*,scalar_t__,int) ;} ;

/* Variables and functions */
 scalar_t__ default_llseek (struct file*,scalar_t__,int) ; 
 scalar_t__ stub1 (struct file*,scalar_t__,int) ; 

__attribute__((used)) static loff_t hppfs_llseek(struct file *file, loff_t off, int where)
{
	struct hppfs_private *data = file->private_data;
	struct file *proc_file = data->proc_file;
	loff_t (*llseek)(struct file *, loff_t, int);
	loff_t ret;

	llseek = proc_file->f_path.dentry->d_inode->i_fop->llseek;
	if (llseek != NULL) {
		ret = (*llseek)(proc_file, off, where);
		if (ret < 0)
			return ret;
	}

	return default_llseek(file, off, where);
}