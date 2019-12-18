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
struct dentry {struct inode* d_inode; TYPE_3__ d_name; } ;
struct TYPE_4__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {int /*<<< orphan*/  flags; int /*<<< orphan*/  vfs_inode; TYPE_2__* volume; TYPE_1__ fid; } ;
struct TYPE_5__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 scalar_t__ AFSNAMEMAX ; 
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 int /*<<< orphan*/  afs_discard_callback_on_delete (struct afs_vnode*) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 int afs_vnode_remove (struct afs_vnode*,struct key*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  clear_nlink (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_rmdir(struct inode *dir, struct dentry *dentry)
{
	struct afs_vnode *dvnode, *vnode;
	struct key *key;
	int ret;

	dvnode = AFS_FS_I(dir);

	_enter("{%x:%u},{%s}",
	       dvnode->fid.vid, dvnode->fid.vnode, dentry->d_name.name);

	ret = -ENAMETOOLONG;
	if (dentry->d_name.len >= AFSNAMEMAX)
		goto error;

	key = afs_request_key(dvnode->volume->cell);
	if (IS_ERR(key)) {
		ret = PTR_ERR(key);
		goto error;
	}

	ret = afs_vnode_remove(dvnode, key, dentry->d_name.name, true);
	if (ret < 0)
		goto rmdir_error;

	if (dentry->d_inode) {
		vnode = AFS_FS_I(dentry->d_inode);
		clear_nlink(&vnode->vfs_inode);
		set_bit(AFS_VNODE_DELETED, &vnode->flags);
		afs_discard_callback_on_delete(vnode);
	}

	key_put(key);
	_leave(" = 0");
	return 0;

rmdir_error:
	key_put(key);
error:
	_leave(" = %d", ret);
	return ret;
}