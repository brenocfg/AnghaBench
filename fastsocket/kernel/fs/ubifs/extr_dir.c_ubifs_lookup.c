#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  inum; } ;
struct nameidata {int dummy; } ;
struct inode {TYPE_2__* i_sb; int /*<<< orphan*/  i_ino; } ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_1__ d_name; } ;
struct TYPE_6__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENAMETOOLONG ; 
 int ENOENT ; 
 int ENOMEM ; 
 struct dentry* ERR_PTR (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 int /*<<< orphan*/  UBIFS_MAX_DENT_NODE_SZ ; 
 scalar_t__ UBIFS_MAX_NLEN ; 
 int /*<<< orphan*/  d_add (struct dentry*,struct inode*) ; 
 scalar_t__ dbg_check_name (struct ubifs_dent_node*,TYPE_1__*) ; 
 int /*<<< orphan*/  dbg_gen (char*,...) ; 
 int /*<<< orphan*/  dent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_err (char*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 struct inode* ubifs_iget (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ubifs_ro_mode (struct ubifs_info*,int) ; 
 int ubifs_tnc_lookup_nm (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,TYPE_1__*) ; 

__attribute__((used)) static struct dentry *ubifs_lookup(struct inode *dir, struct dentry *dentry,
				   struct nameidata *nd)
{
	int err;
	union ubifs_key key;
	struct inode *inode = NULL;
	struct ubifs_dent_node *dent;
	struct ubifs_info *c = dir->i_sb->s_fs_info;

	dbg_gen("'%.*s' in dir ino %lu",
		dentry->d_name.len, dentry->d_name.name, dir->i_ino);

	if (dentry->d_name.len > UBIFS_MAX_NLEN)
		return ERR_PTR(-ENAMETOOLONG);

	dent = kmalloc(UBIFS_MAX_DENT_NODE_SZ, GFP_NOFS);
	if (!dent)
		return ERR_PTR(-ENOMEM);

	dent_key_init(c, &key, dir->i_ino, &dentry->d_name);

	err = ubifs_tnc_lookup_nm(c, &key, dent, &dentry->d_name);
	if (err) {
		if (err == -ENOENT) {
			dbg_gen("not found");
			goto done;
		}
		goto out;
	}

	if (dbg_check_name(dent, &dentry->d_name)) {
		err = -EINVAL;
		goto out;
	}

	inode = ubifs_iget(dir->i_sb, le64_to_cpu(dent->inum));
	if (IS_ERR(inode)) {
		/*
		 * This should not happen. Probably the file-system needs
		 * checking.
		 */
		err = PTR_ERR(inode);
		ubifs_err("dead directory entry '%.*s', error %d",
			  dentry->d_name.len, dentry->d_name.name, err);
		ubifs_ro_mode(c, err);
		goto out;
	}

done:
	kfree(dent);
	/*
	 * Note, d_splice_alias() would be required instead if we supported
	 * NFS.
	 */
	d_add(dentry, inode);
	return NULL;

out:
	kfree(dent);
	return ERR_PTR(err);
}