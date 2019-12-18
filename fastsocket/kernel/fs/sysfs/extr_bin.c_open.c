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
struct TYPE_6__ {int /*<<< orphan*/  buffers; struct bin_attribute* bin_attr; } ;
struct sysfs_dirent {TYPE_3__ s_bin_attr; } ;
struct inode {int dummy; } ;
struct TYPE_5__ {TYPE_1__* dentry; } ;
struct file {int f_mode; struct bin_buffer* private_data; TYPE_2__ f_path; } ;
struct bin_buffer {int /*<<< orphan*/  list; struct file* file; int /*<<< orphan*/  mutex; int /*<<< orphan*/  buffer; } ;
struct bin_attribute {scalar_t__ mmap; scalar_t__ read; scalar_t__ write; } ;
struct TYPE_4__ {struct sysfs_dirent* d_fsdata; } ;

/* Variables and functions */
 int EACCES ; 
 int ENODEV ; 
 int ENOMEM ; 
 int FMODE_READ ; 
 int FMODE_WRITE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PAGE_SIZE ; 
 int /*<<< orphan*/  hlist_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct bin_buffer*) ; 
 int /*<<< orphan*/  kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct bin_buffer* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sysfs_bin_lock ; 
 int /*<<< orphan*/  sysfs_get_active_two (struct sysfs_dirent*) ; 
 int /*<<< orphan*/  sysfs_put_active_two (struct sysfs_dirent*) ; 

__attribute__((used)) static int open(struct inode * inode, struct file * file)
{
	struct sysfs_dirent *attr_sd = file->f_path.dentry->d_fsdata;
	struct bin_attribute *attr = attr_sd->s_bin_attr.bin_attr;
	struct bin_buffer *bb = NULL;
	int error;

	/* binary file operations requires both @sd and its parent */
	if (!sysfs_get_active_two(attr_sd))
		return -ENODEV;

	error = -EACCES;
	if ((file->f_mode & FMODE_WRITE) && !(attr->write || attr->mmap))
		goto err_out;
	if ((file->f_mode & FMODE_READ) && !(attr->read || attr->mmap))
		goto err_out;

	error = -ENOMEM;
	bb = kzalloc(sizeof(*bb), GFP_KERNEL);
	if (!bb)
		goto err_out;

	bb->buffer = kmalloc(PAGE_SIZE, GFP_KERNEL);
	if (!bb->buffer)
		goto err_out;

	mutex_init(&bb->mutex);
	bb->file = file;
	file->private_data = bb;

	mutex_lock(&sysfs_bin_lock);
	hlist_add_head(&bb->list, &attr_sd->s_bin_attr.buffers);
	mutex_unlock(&sysfs_bin_lock);

	/* open succeeded, put active references */
	sysfs_put_active_two(attr_sd);
	return 0;

 err_out:
	sysfs_put_active_two(attr_sd);
	kfree(bb);
	return error;
}