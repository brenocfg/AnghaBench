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
struct inode {int dummy; } ;
struct TYPE_5__ {struct dentry* dentry; } ;
struct file {TYPE_1__ f_path; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_4__ d_name; TYPE_3__* d_parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct TYPE_7__ {TYPE_2__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  NFSIOS_VFSRELEASE ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_inc_stats (struct inode*,int /*<<< orphan*/ ) ; 
 int nfs_release (struct inode*,struct file*) ; 

__attribute__((used)) static int
nfs_file_release(struct inode *inode, struct file *filp)
{
	struct dentry *dentry = filp->f_path.dentry;

	dprintk("NFS: release(%s/%s)\n",
			dentry->d_parent->d_name.name,
			dentry->d_name.name);

	nfs_inc_stats(inode, NFSIOS_VFSRELEASE);
	return nfs_release(inode, filp);
}