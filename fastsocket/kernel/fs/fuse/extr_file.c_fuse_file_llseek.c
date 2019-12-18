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
struct inode {int /*<<< orphan*/  i_mutex; TYPE_1__* i_sb; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {int f_pos; scalar_t__ f_version; TYPE_3__ f_path; } ;
typedef  int loff_t ;
struct TYPE_5__ {struct inode* d_inode; } ;
struct TYPE_4__ {int s_maxbytes; } ;

/* Variables and functions */
 int EINVAL ; 
#define  SEEK_CUR 129 
#define  SEEK_END 128 
 int fuse_update_attributes (struct inode*,int /*<<< orphan*/ *,struct file*,int /*<<< orphan*/ *) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t fuse_file_llseek(struct file *file, loff_t offset, int origin)
{
	loff_t retval;
	struct inode *inode = file->f_path.dentry->d_inode;

	mutex_lock(&inode->i_mutex);
	switch (origin) {
	case SEEK_END:
		retval = fuse_update_attributes(inode, NULL, file, NULL);
		if (retval)
			goto exit;
		offset += i_size_read(inode);
		break;
	case SEEK_CUR:
		offset += file->f_pos;
	}
	retval = -EINVAL;
	if (offset >= 0 && offset <= inode->i_sb->s_maxbytes) {
		if (offset != file->f_pos) {
			file->f_pos = offset;
			file->f_version = 0;
		}
		retval = offset;
	}
exit:
	mutex_unlock(&inode->i_mutex);
	return retval;
}