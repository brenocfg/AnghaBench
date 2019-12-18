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
struct super_block {int /*<<< orphan*/  s_flags; int /*<<< orphan*/  s_xattr; TYPE_2__* s_root; } ;
struct dentry {TYPE_3__* d_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  s_mount_opt; struct dentry* xattr_root; struct dentry* priv_root; } ;
struct TYPE_7__ {int /*<<< orphan*/  i_mutex; } ;
struct TYPE_6__ {TYPE_1__* d_inode; } ;
struct TYPE_5__ {int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dentry*) ; 
 int /*<<< orphan*/  MS_POSIXACL ; 
 int MS_RDONLY ; 
 int PTR_ERR (struct dentry*) ; 
 int /*<<< orphan*/  REISERFS_POSIXACL ; 
 TYPE_4__* REISERFS_SB (struct super_block*) ; 
 int /*<<< orphan*/  REISERFS_XATTRS_USER ; 
 int /*<<< orphan*/  XAROOT_NAME ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int create_privroot (struct dentry*) ; 
 struct dentry* lookup_one_len (int /*<<< orphan*/ ,struct dentry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ reiserfs_posixacl (struct super_block*) ; 
 int /*<<< orphan*/  reiserfs_xattr_handlers ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int xattr_mount_check (struct super_block*) ; 

int reiserfs_xattr_init(struct super_block *s, int mount_flags)
{
	int err = 0;
	struct dentry *privroot = REISERFS_SB(s)->priv_root;

	err = xattr_mount_check(s);
	if (err)
		goto error;

	if (!privroot->d_inode && !(mount_flags & MS_RDONLY)) {
		mutex_lock(&s->s_root->d_inode->i_mutex);
		err = create_privroot(REISERFS_SB(s)->priv_root);
		mutex_unlock(&s->s_root->d_inode->i_mutex);
	}

	if (privroot->d_inode) {
		s->s_xattr = reiserfs_xattr_handlers;
		mutex_lock(&privroot->d_inode->i_mutex);
		if (!REISERFS_SB(s)->xattr_root) {
			struct dentry *dentry;
			dentry = lookup_one_len(XAROOT_NAME, privroot,
						strlen(XAROOT_NAME));
			if (!IS_ERR(dentry))
				REISERFS_SB(s)->xattr_root = dentry;
			else
				err = PTR_ERR(dentry);
		}
		mutex_unlock(&privroot->d_inode->i_mutex);
	}

error:
	if (err) {
		clear_bit(REISERFS_XATTRS_USER, &(REISERFS_SB(s)->s_mount_opt));
		clear_bit(REISERFS_POSIXACL, &(REISERFS_SB(s)->s_mount_opt));
	}

	/* The super_block MS_POSIXACL must mirror the (no)acl mount option. */
	if (reiserfs_posixacl(s))
		s->s_flags |= MS_POSIXACL;
	else
		s->s_flags &= ~MS_POSIXACL;

	return err;
}