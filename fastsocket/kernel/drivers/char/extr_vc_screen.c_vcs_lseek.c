#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* dentry; } ;
struct file {int f_pos; TYPE_2__ f_path; } ;
typedef  int loff_t ;
struct TYPE_3__ {int /*<<< orphan*/  d_inode; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  con_buf_mtx ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int vcs_size (int /*<<< orphan*/ ) ; 

__attribute__((used)) static loff_t vcs_lseek(struct file *file, loff_t offset, int orig)
{
	int size;

	mutex_lock(&con_buf_mtx);
	size = vcs_size(file->f_path.dentry->d_inode);
	switch (orig) {
		default:
			mutex_unlock(&con_buf_mtx);
			return -EINVAL;
		case 2:
			offset += size;
			break;
		case 1:
			offset += file->f_pos;
		case 0:
			break;
	}
	if (offset < 0 || offset > size) {
		mutex_unlock(&con_buf_mtx);
		return -EINVAL;
	}
	file->f_pos = offset;
	mutex_unlock(&con_buf_mtx);
	return file->f_pos;
}