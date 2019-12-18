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
struct TYPE_4__ {int /*<<< orphan*/  i_mapping; int /*<<< orphan*/  i_mode; } ;
struct TYPE_3__ {int /*<<< orphan*/  vnode; int /*<<< orphan*/  vid; } ;
struct afs_vnode {TYPE_2__ vfs_inode; TYPE_1__ fid; } ;

/* Variables and functions */
 scalar_t__ S_ISREG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_inode_pages2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidate_remote_inode (TYPE_2__*) ; 

void afs_zap_data(struct afs_vnode *vnode)
{
	_enter("{%x:%u}", vnode->fid.vid, vnode->fid.vnode);

	/* nuke all the non-dirty pages that aren't locked, mapped or being
	 * written back in a regular file and completely discard the pages in a
	 * directory or symlink */
	if (S_ISREG(vnode->vfs_inode.i_mode))
		invalidate_remote_inode(&vnode->vfs_inode);
	else
		invalidate_inode_pages2(vnode->vfs_inode.i_mapping);
}