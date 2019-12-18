#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_ino; } ;
struct TYPE_2__ {int /*<<< orphan*/  unique; int /*<<< orphan*/  vnode; } ;
struct afs_vnode {int /*<<< orphan*/  volume; TYPE_1__ fid; } ;
struct afs_iget_data {int /*<<< orphan*/  volume; TYPE_1__ fid; } ;

/* Variables and functions */
 struct afs_vnode* AFS_FS_I (struct inode*) ; 

__attribute__((used)) static int afs_iget5_set(struct inode *inode, void *opaque)
{
	struct afs_iget_data *data = opaque;
	struct afs_vnode *vnode = AFS_FS_I(inode);

	inode->i_ino = data->fid.vnode;
	inode->i_version = data->fid.unique;
	vnode->fid = data->fid;
	vnode->volume = data->volume;

	return 0;
}