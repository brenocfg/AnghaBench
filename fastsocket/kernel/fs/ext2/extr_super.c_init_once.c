#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ext2_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  truncate_mutex; int /*<<< orphan*/  xattr_sem; int /*<<< orphan*/  i_meta_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rwlock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct ext2_inode_info *ei = (struct ext2_inode_info *) foo;

	rwlock_init(&ei->i_meta_lock);
#ifdef CONFIG_EXT2_FS_XATTR
	init_rwsem(&ei->xattr_sem);
#endif
	mutex_init(&ei->truncate_mutex);
	inode_init_once(&ei->vfs_inode);
}