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
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_4__ {int /*<<< orphan*/  proc_dentry; } ;
struct TYPE_3__ {int /*<<< orphan*/  s_fs_info; } ;

/* Variables and functions */
 TYPE_2__* HPPFS_I (struct inode*) ; 
 int /*<<< orphan*/  clear_inode (struct inode*) ; 
 int /*<<< orphan*/  dput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mntput (int /*<<< orphan*/ ) ; 

void hppfs_delete_inode(struct inode *ino)
{
	dput(HPPFS_I(ino)->proc_dentry);
	mntput(ino->i_sb->s_fs_info);

	clear_inode(ino);
}