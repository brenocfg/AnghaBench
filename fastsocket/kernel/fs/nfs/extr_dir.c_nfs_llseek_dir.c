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
struct nfs_open_dir_context {scalar_t__ duped; scalar_t__ dir_cookie; } ;
struct inode {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {scalar_t__ f_pos; struct nfs_open_dir_context* private_data; TYPE_1__ f_path; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_4__ d_name; TYPE_3__* d_parent; struct inode* d_inode; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  FILE ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static loff_t nfs_llseek_dir(struct file *filp, loff_t offset, int origin)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	struct nfs_open_dir_context *dir_ctx = filp->private_data;

	dfprintk(FILE, "NFS: llseek dir(%s/%s, %lld, %d)\n",
			dentry->d_parent->d_name.name,
			dentry->d_name.name,
			offset, origin);

	mutex_lock(&inode->i_mutex);
	switch (origin) {
		case 1:
			offset += filp->f_pos;
		case 0:
			if (offset >= 0)
				break;
		default:
			offset = -EINVAL;
			goto out;
	}
	if (offset != filp->f_pos) {
		filp->f_pos = offset;
		dir_ctx->dir_cookie = 0;
		dir_ctx->duped = 0;
	}
out:
	mutex_unlock(&inode->i_mutex);
	return offset;
}