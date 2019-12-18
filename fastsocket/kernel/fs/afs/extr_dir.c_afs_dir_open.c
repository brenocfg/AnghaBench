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
typedef  union afs_dirent {int dummy; } afs_dirent ;
typedef  union afs_dir_block {int dummy; } afs_dir_block ;
struct inode {int /*<<< orphan*/  i_ino; } ;
struct file {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 TYPE_1__* AFS_FS_I (struct inode*) ; 
 int /*<<< orphan*/  AFS_VNODE_DELETED ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int ENOENT ; 
 int /*<<< orphan*/  _enter (char*,int /*<<< orphan*/ ) ; 
 int afs_open (struct inode*,struct file*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int afs_dir_open(struct inode *inode, struct file *file)
{
	_enter("{%lu}", inode->i_ino);

	BUILD_BUG_ON(sizeof(union afs_dir_block) != 2048);
	BUILD_BUG_ON(sizeof(union afs_dirent) != 32);

	if (test_bit(AFS_VNODE_DELETED, &AFS_FS_I(inode)->flags))
		return -ENOENT;

	return afs_open(inode, file);
}