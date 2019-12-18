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
struct ncp_entry_info {int /*<<< orphan*/  file_handle; int /*<<< orphan*/  ino; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct TYPE_6__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; TYPE_2__* d_parent; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;
struct TYPE_5__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  NCP_SERVER (struct inode*) ; 
 int /*<<< orphan*/  PPRINTK (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,struct inode*) ; 
 int /*<<< orphan*/  iunique (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ncp_close_file (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct inode* ncp_iget (int /*<<< orphan*/ ,struct ncp_entry_info*) ; 

__attribute__((used)) static int ncp_instantiate(struct inode *dir, struct dentry *dentry,
			struct ncp_entry_info *finfo)
{
	struct inode *inode;
	int error = -EINVAL;

	finfo->ino = iunique(dir->i_sb, 2);
	inode = ncp_iget(dir->i_sb, finfo);
	if (!inode)
		goto out_close;
	d_instantiate(dentry,inode);
	error = 0;
out:
	return error;

out_close:
	PPRINTK("ncp_instantiate: %s/%s failed, closing file\n",
		dentry->d_parent->d_name.name, dentry->d_name.name);
	ncp_close_file(NCP_SERVER(dir), finfo->file_handle);
	goto out;
}