#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_mode; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;
struct dentry {TYPE_2__ d_name; TYPE_4__* d_parent; int /*<<< orphan*/  d_count; struct inode* d_inode; } ;
struct TYPE_10__ {int (* rename ) (struct inode*,TYPE_2__*,struct inode*,TYPE_2__*) ;} ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;
struct TYPE_9__ {TYPE_1__ d_name; } ;

/* Variables and functions */
 int EBUSY ; 
 int ENOENT ; 
 TYPE_6__* NFS_PROTO (struct inode*) ; 
 int /*<<< orphan*/  S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFS ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct dentry* d_alloc (TYPE_4__*,TYPE_2__*) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_move (struct dentry*,struct dentry*) ; 
 int /*<<< orphan*/  d_rehash (struct dentry*) ; 
 int /*<<< orphan*/  d_unhashed (struct dentry*) ; 
 int /*<<< orphan*/  dfprintk (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dput (struct dentry*) ; 
 int /*<<< orphan*/  nfs_dentry_handle_enoent (struct dentry*) ; 
 int /*<<< orphan*/  nfs_drop_nlink (struct inode*) ; 
 int /*<<< orphan*/  nfs_inode_return_delegation (struct inode*) ; 
 int /*<<< orphan*/  nfs_mark_for_revalidate (struct inode*) ; 
 int /*<<< orphan*/  nfs_save_change_attribute (struct inode*) ; 
 int /*<<< orphan*/  nfs_set_verifier (struct dentry*,int /*<<< orphan*/ ) ; 
 int nfs_sillyrename (struct inode*,struct dentry*) ; 
 int stub1 (struct inode*,TYPE_2__*,struct inode*,TYPE_2__*) ; 

__attribute__((used)) static int nfs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry)
{
	struct inode *old_inode = old_dentry->d_inode;
	struct inode *new_inode = new_dentry->d_inode;
	struct dentry *dentry = NULL, *rehash = NULL;
	int error = -EBUSY;

	dfprintk(VFS, "NFS: rename(%s/%s -> %s/%s, ct=%d)\n",
		 old_dentry->d_parent->d_name.name, old_dentry->d_name.name,
		 new_dentry->d_parent->d_name.name, new_dentry->d_name.name,
		 atomic_read(&new_dentry->d_count));

	/*
	 * For non-directories, check whether the target is busy and if so,
	 * make a copy of the dentry and then do a silly-rename. If the
	 * silly-rename succeeds, the copied dentry is hashed and becomes
	 * the new target.
	 */
	if (new_inode && !S_ISDIR(new_inode->i_mode)) {
		/*
		 * To prevent any new references to the target during the
		 * rename, we unhash the dentry in advance.
		 */
		if (!d_unhashed(new_dentry)) {
			d_drop(new_dentry);
			rehash = new_dentry;
		}

		if (atomic_read(&new_dentry->d_count) > 2) {
			int err;

			/* copy the target dentry's name */
			dentry = d_alloc(new_dentry->d_parent,
					 &new_dentry->d_name);
			if (!dentry)
				goto out;

			/* silly-rename the existing target ... */
			err = nfs_sillyrename(new_dir, new_dentry);
			if (err)
				goto out;

			new_dentry = dentry;
			rehash = NULL;
			new_inode = NULL;
		}
	}

	nfs_inode_return_delegation(old_inode);
	if (new_inode != NULL)
		nfs_inode_return_delegation(new_inode);

	error = NFS_PROTO(old_dir)->rename(old_dir, &old_dentry->d_name,
					   new_dir, &new_dentry->d_name);
	nfs_mark_for_revalidate(old_inode);
out:
	if (rehash)
		d_rehash(rehash);
	if (!error) {
		if (new_inode != NULL)
			nfs_drop_nlink(new_inode);
		d_move(old_dentry, new_dentry);
		nfs_set_verifier(new_dentry,
					nfs_save_change_attribute(new_dir));
	} else if (error == -ENOENT)
		nfs_dentry_handle_enoent(old_dentry);

	/* new dentry created? */
	if (dentry)
		dput(dentry);
	return error;
}