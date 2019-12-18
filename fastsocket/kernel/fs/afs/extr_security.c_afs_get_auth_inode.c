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
struct TYPE_5__ {int /*<<< orphan*/  vnode; } ;
struct TYPE_4__ {int /*<<< orphan*/  parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_mode; } ;
struct afs_vnode {TYPE_2__ fid; TYPE_1__ status; TYPE_3__ vfs_inode; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 struct afs_vnode* ERR_CAST (struct inode*) ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*) ; 
 int /*<<< orphan*/  _leave (char*,int /*<<< orphan*/ ) ; 
 struct inode* afs_iget (int /*<<< orphan*/ ,struct key*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 struct inode* igrab (TYPE_3__*) ; 

__attribute__((used)) static struct afs_vnode *afs_get_auth_inode(struct afs_vnode *vnode,
					    struct key *key)
{
	struct afs_vnode *auth_vnode;
	struct inode *auth_inode;

	_enter("");

	if (S_ISDIR(vnode->vfs_inode.i_mode)) {
		auth_inode = igrab(&vnode->vfs_inode);
		ASSERT(auth_inode != NULL);
	} else {
		auth_inode = afs_iget(vnode->vfs_inode.i_sb, key,
				      &vnode->status.parent, NULL, NULL);
		if (IS_ERR(auth_inode))
			return ERR_CAST(auth_inode);
	}

	auth_vnode = AFS_FS_I(auth_inode);
	_leave(" = {%x}", auth_vnode->fid.vnode);
	return auth_vnode;
}