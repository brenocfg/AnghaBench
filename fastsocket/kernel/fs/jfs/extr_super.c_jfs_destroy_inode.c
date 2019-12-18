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
struct jfs_inode_info {int active_ag; int /*<<< orphan*/  ag_lock; int /*<<< orphan*/  anon_inode_list; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct bmap {int /*<<< orphan*/ * db_active; } ;
struct TYPE_2__ {struct bmap* bmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct jfs_inode_info* JFS_IP (struct inode*) ; 
 TYPE_1__* JFS_SBI (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  jfs_inode_cachep ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct jfs_inode_info*) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void jfs_destroy_inode(struct inode *inode)
{
	struct jfs_inode_info *ji = JFS_IP(inode);

	BUG_ON(!list_empty(&ji->anon_inode_list));

	spin_lock_irq(&ji->ag_lock);
	if (ji->active_ag != -1) {
		struct bmap *bmap = JFS_SBI(inode->i_sb)->bmap;
		atomic_dec(&bmap->db_active[ji->active_ag]);
		ji->active_ag = -1;
	}
	spin_unlock_irq(&ji->ag_lock);
	kmem_cache_free(jfs_inode_cachep, ji);
}