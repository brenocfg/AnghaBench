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
struct inode {int /*<<< orphan*/  i_count; } ;
struct delayed_iput {int /*<<< orphan*/  list; struct inode* inode; } ;
struct btrfs_fs_info {int /*<<< orphan*/  delayed_iput_lock; int /*<<< orphan*/  delayed_iputs; } ;
struct TYPE_4__ {TYPE_1__* root; } ;
struct TYPE_3__ {struct btrfs_fs_info* fs_info; } ;

/* Variables and functions */
 TYPE_2__* BTRFS_I (struct inode*) ; 
 int GFP_NOFS ; 
 int __GFP_NOFAIL ; 
 scalar_t__ atomic_add_unless (int /*<<< orphan*/ *,int,int) ; 
 struct delayed_iput* kmalloc (int,int) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

void btrfs_add_delayed_iput(struct inode *inode)
{
	struct btrfs_fs_info *fs_info = BTRFS_I(inode)->root->fs_info;
	struct delayed_iput *delayed;

	if (atomic_add_unless(&inode->i_count, -1, 1))
		return;

	delayed = kmalloc(sizeof(*delayed), GFP_NOFS | __GFP_NOFAIL);
	delayed->inode = inode;

	spin_lock(&fs_info->delayed_iput_lock);
	list_add_tail(&delayed->list, &fs_info->delayed_iputs);
	spin_unlock(&fs_info->delayed_iput_lock);
}