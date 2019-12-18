#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  ohandle; int /*<<< orphan*/  ohandlen; } ;
typedef  TYPE_1__ xfs_fsop_handlereq_t ;
struct file {int dummy; } ;
struct dentry {TYPE_4__* d_inode; } ;
typedef  int /*<<< orphan*/  __u32 ;
struct TYPE_6__ {int /*<<< orphan*/  i_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int /*<<< orphan*/  EFAULT ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  EPERM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 scalar_t__ MAXPATHLEN ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  S_ISLNK (int /*<<< orphan*/ ) ; 
 int XFS_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XFS_I (TYPE_4__*) ; 
 int /*<<< orphan*/  capable (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_from_user (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int do_readlink (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  kfree (void*) ; 
 void* kmalloc (scalar_t__,int /*<<< orphan*/ ) ; 
 struct dentry* xfs_handlereq_to_dentry (struct file*,TYPE_1__*) ; 
 int xfs_readlink (int /*<<< orphan*/ ,void*) ; 

int
xfs_readlink_by_handle(
	struct file		*parfilp,
	xfs_fsop_handlereq_t	*hreq)
{
	struct dentry		*dentry;
	__u32			olen;
	void			*link;
	int			error;

	if (!capable(CAP_SYS_ADMIN))
		return -XFS_ERROR(EPERM);

	dentry = xfs_handlereq_to_dentry(parfilp, hreq);
	if (IS_ERR(dentry))
		return PTR_ERR(dentry);

	/* Restrict this handle operation to symlinks only. */
	if (!S_ISLNK(dentry->d_inode->i_mode)) {
		error = -XFS_ERROR(EINVAL);
		goto out_dput;
	}

	if (copy_from_user(&olen, hreq->ohandlen, sizeof(__u32))) {
		error = -XFS_ERROR(EFAULT);
		goto out_dput;
	}

	link = kmalloc(MAXPATHLEN+1, GFP_KERNEL);
	if (!link) {
		error = -XFS_ERROR(ENOMEM);
		goto out_dput;
	}

	error = -xfs_readlink(XFS_I(dentry->d_inode), link);
	if (error)
		goto out_kfree;
	error = do_readlink(hreq->ohandle, olen, link);
	if (error)
		goto out_kfree;

 out_kfree:
	kfree(link);
 out_dput:
	dput(dentry);
	return error;
}