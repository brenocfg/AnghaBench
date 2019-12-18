#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct nameidata {int dummy; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct fuse_entry_out {int dummy; } ;
struct dentry {int /*<<< orphan*/ * d_op; int /*<<< orphan*/  d_name; } ;

/* Variables and functions */
 int EIO ; 
 int ENOENT ; 
 struct dentry* ERR_PTR (int) ; 
 scalar_t__ FUSE_ROOT_ID ; 
 scalar_t__ IS_ERR (struct dentry*) ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  fuse_change_entry_timeout (struct dentry*,struct fuse_entry_out*) ; 
 int /*<<< orphan*/  fuse_dentry_operations ; 
 int /*<<< orphan*/  fuse_invalidate_entry_cache (struct dentry*) ; 
 int fuse_lookup_name (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,struct fuse_entry_out*,struct inode**) ; 
 struct dentry* fuse_materialise_dentry (struct dentry*,struct inode*) ; 
 scalar_t__ get_node_id (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

__attribute__((used)) static struct dentry *fuse_lookup(struct inode *dir, struct dentry *entry,
				  struct nameidata *nd)
{
	int err;
	struct fuse_entry_out outarg;
	struct inode *inode;
	struct dentry *newent;
	bool outarg_valid = true;

	err = fuse_lookup_name(dir->i_sb, get_node_id(dir), &entry->d_name,
			       &outarg, &inode);
	if (err == -ENOENT) {
		outarg_valid = false;
		err = 0;
	}
	if (err)
		goto out_err;

	err = -EIO;
	if (inode && get_node_id(inode) == FUSE_ROOT_ID)
		goto out_iput;

	newent = fuse_materialise_dentry(entry, inode);
	err = PTR_ERR(newent);
	if (IS_ERR(newent))
		goto out_err;

	entry = newent ? newent : entry;
	entry->d_op = &fuse_dentry_operations;
	if (outarg_valid)
		fuse_change_entry_timeout(entry, &outarg);
	else
		fuse_invalidate_entry_cache(entry);

	return newent;

 out_iput:
	iput(inode);
 out_err:
	return ERR_PTR(err);
}