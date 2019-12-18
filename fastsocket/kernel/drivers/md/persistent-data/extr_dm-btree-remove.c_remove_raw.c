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
typedef  int /*<<< orphan*/  uint64_t ;
struct shadow_spine {int dummy; } ;
struct dm_btree_value_type {int dummy; } ;
struct dm_btree_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  flags; } ;
struct btree_node {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  dm_block_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 int LEAF_NODE ; 
 int /*<<< orphan*/  cpu_to_le64 (int /*<<< orphan*/ ) ; 
 struct btree_node* dm_block_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_block_location (int /*<<< orphan*/ ) ; 
 int do_leaf (struct btree_node*,int /*<<< orphan*/ ,unsigned int*) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_bound (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int rebalance_children (struct shadow_spine*,struct dm_btree_info*,struct dm_btree_value_type*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  shadow_current (struct shadow_spine*) ; 
 scalar_t__ shadow_has_parent (struct shadow_spine*) ; 
 int /*<<< orphan*/  shadow_parent (struct shadow_spine*) ; 
 int shadow_step (struct shadow_spine*,int /*<<< orphan*/ ,struct dm_btree_value_type*) ; 
 int /*<<< orphan*/  value64 (struct btree_node*,int) ; 
 int /*<<< orphan*/  value_ptr (struct btree_node*,int) ; 

__attribute__((used)) static int remove_raw(struct shadow_spine *s, struct dm_btree_info *info,
		      struct dm_btree_value_type *vt, dm_block_t root,
		      uint64_t key, unsigned *index)
{
	int i = *index, r;
	struct btree_node *n;

	for (;;) {
		r = shadow_step(s, root, vt);
		if (r < 0)
			break;

		/*
		 * We have to patch up the parent node, ugly, but I don't
		 * see a way to do this automatically as part of the spine
		 * op.
		 */
		if (shadow_has_parent(s)) {
			__le64 location = cpu_to_le64(dm_block_location(shadow_current(s)));
			memcpy(value_ptr(dm_block_data(shadow_parent(s)), i),
			       &location, sizeof(__le64));
		}

		n = dm_block_data(shadow_current(s));

		if (le32_to_cpu(n->header.flags) & LEAF_NODE)
			return do_leaf(n, key, index);

		r = rebalance_children(s, info, vt, key);
		if (r)
			break;

		n = dm_block_data(shadow_current(s));
		if (le32_to_cpu(n->header.flags) & LEAF_NODE)
			return do_leaf(n, key, index);

		i = lower_bound(n, key);

		/*
		 * We know the key is present, or else
		 * rebalance_children would have returned
		 * -ENODATA
		 */
		root = value64(n, i);
	}

	return r;
}