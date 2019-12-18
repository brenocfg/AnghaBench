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
struct key {int dummy; } ;
struct inode {int dummy; } ;
struct TYPE_7__ {scalar_t__ len; int /*<<< orphan*/  name; } ;
struct dentry {TYPE_3__ d_name; struct inode* d_inode; } ;
struct TYPE_8__ {int /*<<< orphan*/  i_count; } ;
struct TYPE_5__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_4__ vfs_inode; TYPE_2__* volume; TYPE_1__ fid; } ;
struct TYPE_6__ {int /*<<< orphan*/  cell; } ;

/* Variables and functions */
 scalar_t__ AFSNAMEMAX ; 
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int ENAMETOOLONG ; 
 scalar_t__ IS_ERR (struct key*) ; 
 int PTR_ERR (struct key*) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _leave (char*,...) ; 
 struct key* afs_request_key (int /*<<< orphan*/ ) ; 
 int afs_vnode_link (struct afs_vnode*,struct afs_vnode*,struct key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  d_drop (struct dentry*) ; 
 int /*<<< orphan*/  d_instantiate (struct dentry*,TYPE_4__*) ; 
 int /*<<< orphan*/  key_put (struct key*) ; 

__attribute__((used)) static int afs_link(struct dentry *from, struct inode *dir,
		    struct dentry *dentry)
{
	struct afs_vnode *dvnode, *vnode;
	struct key *key;
	int ret;

	vnode = AFS_FS_I(from->d_inode);
	dvnode = AFS_FS_I(dir);

	_enter("{%x:%u},{%x:%u},{%s}",
	       vnode->fid.vid, vnode->fid.vnode,
	       dvnode->fid.vid, dvnode->fid.vnode,
	       dentry->d_name.name);

	ret = -ENAMETOOLONG;
	if (dentry->d_name.len >= AFSNAMEMAX)
		goto error;

	key = afs_request_key(dvnode->volume->cell);
	if (IS_ERR(key)) {
		ret = PTR_ERR(key);
		goto error;
	}

	ret = afs_vnode_link(dvnode, vnode, key, dentry->d_name.name);
	if (ret < 0)
		goto link_error;

	atomic_inc(&vnode->vfs_inode.i_count);
	d_instantiate(dentry, &vnode->vfs_inode);
	key_put(key);
	_leave(" = 0");
	return 0;

link_error:
	key_put(key);
error:
	d_drop(dentry);
	_leave(" = %d", ret);
	return ret;
}