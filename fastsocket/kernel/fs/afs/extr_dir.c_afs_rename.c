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
struct key {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_6__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; struct inode* d_inode; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_2__* volume; TYPE_1__ fid; } ;
struct TYPE_5__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 scalar_t__ AFSNAMEMAX ; 
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 int afs_vnode_rename (struct afs_vnode*,struct afs_vnode*,struct key*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 

__attribute__((used)) static int afs_rename(struct inode *old_dir, struct dentry *old_dentry,
		      struct inode *new_dir, struct dentry *new_dentry)
{
	struct afs_vnode *orig_dvnode, *new_dvnode, *vnode;
	struct key *key;
	int ret;

	vnode = AFS_FS_I(old_dentry->d_inode);
	orig_dvnode = AFS_FS_I(old_dir);
	new_dvnode = AFS_FS_I(new_dir);

	_enter("{%x:%u},{%x:%u},{%x:%u},{%s}",
	       orig_dvnode->fid.vid, orig_dvnode->fid.vnode,
	       vnode->fid.vid, vnode->fid.vnode,
	       new_dvnode->fid.vid, new_dvnode->fid.vnode,
	       new_dentry->d_name.name);

	ret = -ENAMETOOLONG;
	if (new_dentry->d_name.len >= AFSNAMEMAX)
		goto error;

	key = afs_request_key(orig_dvnode->volume->cell);
	if (IS_ERR(key)) {
		ret = PTR_ERR(key);
		goto error;
	}

	ret = afs_vnode_rename(orig_dvnode, new_dvnode, key,
			       old_dentry->d_name.name,
			       new_dentry->d_name.name);
	if (ret < 0)
		goto rename_error;
	key_put(key);
	_leave(" = 0");
	return 0;

rename_error:
	key_put(key);
error:
	d_drop(new_dentry);
	_leave(" = %d", ret);
	return ret;
}