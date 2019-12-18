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
typedef  union ubifs_key {int dummy; } ubifs_key ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  inum; } ;
struct qstr {char const* name; int /*<<< orphan*/  len; } ;
struct inode {int /*<<< orphan*/  i_ino; int /*<<< orphan*/  i_mutex; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int EEXIST ; 
 int ENODATA ; 
 int ENOENT ; 
 int ENOMEM ; 
 int ERANGE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 int PTR_ERR (struct inode*) ; 
 size_t UBIFS_MAX_INO_DATA ; 
 int /*<<< orphan*/  UBIFS_MAX_XENT_NODE_SZ ; 
 int XATTR_CREATE ; 
 int XATTR_REPLACE ; 
 int change_xattr (struct ubifs_info*,struct inode*,struct inode*,void const*,size_t) ; 
 int check_namespace (struct qstr*) ; 
 int create_xattr (struct ubifs_info*,struct inode*,struct qstr*,void const*,size_t) ; 
 int /*<<< orphan*/  dbg_gen (char*,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 struct inode* iget_xattr (struct ubifs_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 struct ubifs_dent_node* kmalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_is_locked (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  ubifs_assert (int /*<<< orphan*/ ) ; 
 int ubifs_tnc_lookup_nm (struct ubifs_info*,union ubifs_key*,struct ubifs_dent_node*,struct qstr*) ; 
 int /*<<< orphan*/  xent_key_init (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ,struct qstr*) ; 

int ubifs_setxattr(struct dentry *dentry, const char *name,
		   const void *value, size_t size, int flags)
{
	struct inode *inode, *host = dentry->d_inode;
	struct ubifs_info *c = host->i_sb->s_fs_info;
	struct qstr nm = { .name = name, .len = strlen(name) };
	struct ubifs_dent_node *xent;
	union ubifs_key key;
	int err, type;

	dbg_gen("xattr '%s', host ino %lu ('%.*s'), size %zd", name,
		host->i_ino, dentry->d_name.len, dentry->d_name.name, size);
	ubifs_assert(mutex_is_locked(&host->i_mutex));

	if (size > UBIFS_MAX_INO_DATA)
		return -ERANGE;

	type = check_namespace(&nm);
	if (type < 0)
		return type;

	xent = kmalloc(UBIFS_MAX_XENT_NODE_SZ, GFP_NOFS);
	if (!xent)
		return -ENOMEM;

	/*
	 * The extended attribute entries are stored in LNC, so multiple
	 * look-ups do not involve reading the flash.
	 */
	xent_key_init(c, &key, host->i_ino, &nm);
	err = ubifs_tnc_lookup_nm(c, &key, xent, &nm);
	if (err) {
		if (err != -ENOENT)
			goto out_free;

		if (flags & XATTR_REPLACE)
			/* We are asked not to create the xattr */
			err = -ENODATA;
		else
			err = create_xattr(c, host, &nm, value, size);
		goto out_free;
	}

	if (flags & XATTR_CREATE) {
		/* We are asked not to replace the xattr */
		err = -EEXIST;
		goto out_free;
	}

	inode = iget_xattr(c, le64_to_cpu(xent->inum));
	if (IS_ERR(inode)) {
		err = PTR_ERR(inode);
		goto out_free;
	}

	err = change_xattr(c, host, inode, value, size);
	iput(inode);

out_free:
	kfree(xent);
	return err;
}