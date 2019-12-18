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
struct pipe_inode_info {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {struct dentry* dentry; } ;
struct file {int /*<<< orphan*/  f_mapping; TYPE_2__ f_path; } ;
struct TYPE_5__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; TYPE_4__* d_parent; struct inode* d_inode; } ;
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ loff_t ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_8__ {TYPE_3__ d_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long,unsigned long long) ; 
 scalar_t__ generic_file_splice_read (struct file*,scalar_t__*,struct pipe_inode_info*,size_t,unsigned int) ; 
 scalar_t__ nfs_revalidate_mapping (struct inode*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
nfs_file_splice_read(struct file *filp, loff_t *ppos,
		     struct pipe_inode_info *pipe, size_t count,
		     unsigned int flags)
{
	struct dentry *dentry = filp->f_path.dentry;
	struct inode *inode = dentry->d_inode;
	ssize_t res;

	dprintk("NFS: splice_read(%s/%s, %lu@%Lu)\n",
		dentry->d_parent->d_name.name, dentry->d_name.name,
		(unsigned long) count, (unsigned long long) *ppos);

	res = nfs_revalidate_mapping(inode, filp->f_mapping);
	if (!res)
		res = generic_file_splice_read(filp, ppos, pipe, count, flags);
	return res;
}