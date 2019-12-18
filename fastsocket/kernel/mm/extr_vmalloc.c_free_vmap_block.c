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
struct vmap_block {int /*<<< orphan*/  rcu_head; TYPE_1__* va; } ;
struct TYPE_2__ {int /*<<< orphan*/  va_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long addr_to_vb_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_vmap_area_noflush (TYPE_1__*) ; 
 struct vmap_block* radix_tree_delete (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  rcu_free_vb ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vmap_block_tree ; 
 int /*<<< orphan*/  vmap_block_tree_lock ; 

__attribute__((used)) static void free_vmap_block(struct vmap_block *vb)
{
	struct vmap_block *tmp;
	unsigned long vb_idx;

	vb_idx = addr_to_vb_idx(vb->va->va_start);
	spin_lock(&vmap_block_tree_lock);
	tmp = radix_tree_delete(&vmap_block_tree, vb_idx);
	spin_unlock(&vmap_block_tree_lock);
	BUG_ON(tmp != vb);

	free_vmap_area_noflush(vb->va);
	call_rcu(&vb->rcu_head, rcu_free_vb);
}