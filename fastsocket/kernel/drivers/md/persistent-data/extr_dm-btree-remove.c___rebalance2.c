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
typedef  unsigned int uint32_t ;
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
struct child {int /*<<< orphan*/  index; int /*<<< orphan*/  block; struct btree_node* n; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct btree_node {int /*<<< orphan*/ * keys; TYPE_1__ header; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  delete_at (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * key_ptr (struct btree_node*,int /*<<< orphan*/ ) ; 
 unsigned int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int merge_threshold (struct btree_node*) ; 
 int /*<<< orphan*/  node_copy (struct btree_node*,struct btree_node*,unsigned int) ; 
 int /*<<< orphan*/  shift (struct btree_node*,struct btree_node*,unsigned int) ; 

__attribute__((used)) static void __rebalance2(struct dm_btree_info *info, struct btree_node *parent,
			 struct child *l, struct child *r)
{
	struct btree_node *left = l->n;
	struct btree_node *right = r->n;
	uint32_t nr_left = le32_to_cpu(left->header.nr_entries);
	uint32_t nr_right = le32_to_cpu(right->header.nr_entries);
	unsigned threshold = 2 * merge_threshold(left) + 1;

	if (nr_left + nr_right < threshold) {
		/*
		 * Merge
		 */
		node_copy(left, right, -nr_right);
		left->header.nr_entries = cpu_to_le32(nr_left + nr_right);
		delete_at(parent, r->index);

		/*
		 * We need to decrement the right block, but not it's
		 * children, since they're still referenced by left.
		 */
		dm_tm_dec(info->tm, dm_block_location(r->block));
	} else {
		/*
		 * Rebalance.
		 */
		unsigned target_left = (nr_left + nr_right) / 2;
		shift(left, right, nr_left - target_left);
		*key_ptr(parent, r->index) = right->keys[0];
	}
}