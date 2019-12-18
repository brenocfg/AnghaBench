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
struct TYPE_2__ {int /*<<< orphan*/  i_mmap_nonlinear; int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  private_lock; int /*<<< orphan*/  private_list; int /*<<< orphan*/  i_mmap_lock; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;
struct inode {int /*<<< orphan*/  i_fsnotify_mark_entries; int /*<<< orphan*/  inotify_mutex; int /*<<< orphan*/  inotify_watches; TYPE_1__ i_data; int /*<<< orphan*/  i_devices; int /*<<< orphan*/  i_dentry; int /*<<< orphan*/  i_hash; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_HLIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RAW_PRIO_TREE_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  i_size_ordered_init (struct inode*) ; 
 int /*<<< orphan*/  memset (struct inode*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void inode_init_once(struct inode *inode)
{
	memset(inode, 0, sizeof(*inode));
	INIT_HLIST_NODE(&inode->i_hash);
	INIT_LIST_HEAD(&inode->i_dentry);
	INIT_LIST_HEAD(&inode->i_devices);
	INIT_RADIX_TREE(&inode->i_data.page_tree, GFP_ATOMIC);
	spin_lock_init(&inode->i_data.tree_lock);
	spin_lock_init(&inode->i_data.i_mmap_lock);
	INIT_LIST_HEAD(&inode->i_data.private_list);
	spin_lock_init(&inode->i_data.private_lock);
	INIT_RAW_PRIO_TREE_ROOT(&inode->i_data.i_mmap);
	INIT_LIST_HEAD(&inode->i_data.i_mmap_nonlinear);
	i_size_ordered_init(inode);
#ifdef CONFIG_INOTIFY
	INIT_LIST_HEAD(&inode->inotify_watches);
	mutex_init(&inode->inotify_mutex);
#endif
#ifdef CONFIG_FSNOTIFY
	INIT_HLIST_HEAD(&inode->i_fsnotify_mark_entries);
#endif
}