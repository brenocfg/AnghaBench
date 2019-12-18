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
struct address_space {int /*<<< orphan*/  i_mmap_nonlinear; int /*<<< orphan*/  i_mmap; int /*<<< orphan*/  i_mmap_lock; int /*<<< orphan*/  private_lock; int /*<<< orphan*/  private_list; int /*<<< orphan*/  tree_lock; int /*<<< orphan*/  page_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_RADIX_TREE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_RAW_PRIO_TREE_ROOT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memset (struct address_space*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

void nilfs_btnode_cache_init_once(struct address_space *btnc)
{
	memset(btnc, 0, sizeof(*btnc));
	INIT_RADIX_TREE(&btnc->page_tree, GFP_ATOMIC);
	spin_lock_init(&btnc->tree_lock);
	INIT_LIST_HEAD(&btnc->private_list);
	spin_lock_init(&btnc->private_lock);

	spin_lock_init(&btnc->i_mmap_lock);
	INIT_RAW_PRIO_TREE_ROOT(&btnc->i_mmap);
	INIT_LIST_HEAD(&btnc->i_mmap_nonlinear);
}