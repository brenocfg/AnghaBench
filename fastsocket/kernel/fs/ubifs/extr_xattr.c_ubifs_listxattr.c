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
struct ubifs_inode {int xattr_names; int xattr_cnt; } ;
struct ubifs_info {int dummy; } ;
struct ubifs_dent_node {int /*<<< orphan*/  key; int /*<<< orphan*/  nlen; int /*<<< orphan*/ * name; } ;
struct qstr {scalar_t__ len; int /*<<< orphan*/ * name; } ;
struct inode {int /*<<< orphan*/  i_ino; TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; int /*<<< orphan*/  len; } ;
struct dentry {TYPE_2__ d_name; struct inode* d_inode; } ;
typedef  int ssize_t ;
struct TYPE_3__ {struct ubifs_info* s_fs_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_SYS_ADMIN ; 
 int ENOENT ; 
 int ERANGE ; 
 scalar_t__ IS_ERR (struct ubifs_dent_node*) ; 
 int PTR_ERR (struct ubifs_dent_node*) ; 
 int TRUSTED_XATTR ; 
 scalar_t__ capable (int /*<<< orphan*/ ) ; 
 int check_namespace (struct qstr*) ; 
 int /*<<< orphan*/  dbg_gen (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  key_read (struct ubifs_info*,int /*<<< orphan*/ *,union ubifs_key*) ; 
 int /*<<< orphan*/  kfree (struct ubifs_dent_node*) ; 
 scalar_t__ le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lowest_xent_key (struct ubifs_info*,union ubifs_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ubifs_assert (int) ; 
 int /*<<< orphan*/  ubifs_err (char*,int) ; 
 struct ubifs_inode* ubifs_inode (struct inode*) ; 
 struct ubifs_dent_node* ubifs_tnc_next_ent (struct ubifs_info*,union ubifs_key*,struct qstr*) ; 
 scalar_t__ unlikely (int) ; 

ssize_t ubifs_listxattr(struct dentry *dentry, char *buffer, size_t size)
{
	union ubifs_key key;
	struct inode *host = dentry->d_inode;
	struct ubifs_info *c = host->i_sb->s_fs_info;
	struct ubifs_inode *host_ui = ubifs_inode(host);
	struct ubifs_dent_node *xent, *pxent = NULL;
	int err, len, written = 0;
	struct qstr nm = { .name = NULL };

	dbg_gen("ino %lu ('%.*s'), buffer size %zd", host->i_ino,
		dentry->d_name.len, dentry->d_name.name, size);

	len = host_ui->xattr_names + host_ui->xattr_cnt;
	if (!buffer)
		/*
		 * We should return the minimum buffer size which will fit a
		 * null-terminated list of all the extended attribute names.
		 */
		return len;

	if (len > size)
		return -ERANGE;

	lowest_xent_key(c, &key, host->i_ino);
	while (1) {
		int type;

		xent = ubifs_tnc_next_ent(c, &key, &nm);
		if (IS_ERR(xent)) {
			err = PTR_ERR(xent);
			break;
		}

		nm.name = xent->name;
		nm.len = le16_to_cpu(xent->nlen);

		type = check_namespace(&nm);
		if (unlikely(type < 0)) {
			err = type;
			break;
		}

		/* Show trusted namespace only for "power" users */
		if (type != TRUSTED_XATTR || capable(CAP_SYS_ADMIN)) {
			memcpy(buffer + written, nm.name, nm.len + 1);
			written += nm.len + 1;
		}

		kfree(pxent);
		pxent = xent;
		key_read(c, &xent->key, &key);
	}

	kfree(pxent);
	if (err != -ENOENT) {
		ubifs_err("cannot find next direntry, error %d", err);
		return err;
	}

	ubifs_assert(written <= size);
	return written;
}