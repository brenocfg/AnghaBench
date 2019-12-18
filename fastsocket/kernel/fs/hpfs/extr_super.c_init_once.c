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
struct hpfs_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  i_parent_mutex; int /*<<< orphan*/  i_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct hpfs_inode_info *ei = (struct hpfs_inode_info *) foo;

	mutex_init(&ei->i_mutex);
	mutex_init(&ei->i_parent_mutex);
	inode_init_once(&ei->vfs_inode);
}