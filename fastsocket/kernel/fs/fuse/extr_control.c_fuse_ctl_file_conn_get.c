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
struct fuse_conn {int dummy; } ;
struct TYPE_6__ {TYPE_2__* dentry; } ;
struct file {TYPE_3__ f_path; } ;
struct TYPE_5__ {TYPE_1__* d_inode; } ;
struct TYPE_4__ {struct fuse_conn* i_private; } ;

/* Variables and functions */
 struct fuse_conn* fuse_conn_get (struct fuse_conn*) ; 
 int /*<<< orphan*/  fuse_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct fuse_conn *fuse_ctl_file_conn_get(struct file *file)
{
	struct fuse_conn *fc;
	mutex_lock(&fuse_mutex);
	fc = file->f_path.dentry->d_inode->i_private;
	if (fc)
		fc = fuse_conn_get(fc);
	mutex_unlock(&fuse_mutex);
	return fc;
}