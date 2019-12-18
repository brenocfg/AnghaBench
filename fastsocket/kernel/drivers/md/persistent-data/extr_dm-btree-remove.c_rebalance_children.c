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
typedef  int /*<<< orphan*/  uint32_t ;
struct shadow_spine {int dummy; } ;
struct dm_btree_value_type {int dummy; } ;
struct dm_btree_info {int /*<<< orphan*/  tm; } ;
struct dm_block {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  nr_entries; } ;
struct btree_node {TYPE_1__ header; } ;
typedef  int /*<<< orphan*/  dm_block_t ;

/* Variables and functions */
 int ENODATA ; 
 int /*<<< orphan*/  btree_node_validator ; 
 struct btree_node* dm_block_data (struct dm_block*) ; 
 int /*<<< orphan*/  dm_block_location (struct dm_block*) ; 
 int /*<<< orphan*/  dm_bm_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_dec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dm_tm_get_bm (int /*<<< orphan*/ ) ; 
 int dm_tm_read_lock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct dm_block**) ; 
 int dm_tm_unlock (int /*<<< orphan*/ ,struct dm_block*) ; 
 int get_nr_entries (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int le32_to_cpu (int /*<<< orphan*/ ) ; 
 int lower_bound (struct btree_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (struct btree_node*,struct btree_node*,int /*<<< orphan*/ ) ; 
 int rebalance2 (struct shadow_spine*,struct dm_btree_info*,struct dm_btree_value_type*,int) ; 
 int rebalance3 (struct shadow_spine*,struct dm_btree_info*,struct dm_btree_value_type*,int) ; 
 struct dm_block* shadow_current (struct shadow_spine*) ; 
 int /*<<< orphan*/  value64 (struct btree_node*,int) ; 

__attribute__((used)) static int rebalance_children(struct shadow_spine *s,
			      struct dm_btree_info *info,
			      struct dm_btree_value_type *vt, uint64_t key)
{
	int i, r, has_left_sibling, has_right_sibling;
	uint32_t child_entries;
	struct btree_node *n;

	n = dm_block_data(shadow_current(s));

	if (le32_to_cpu(n->header.nr_entries) == 1) {
		struct dm_block *child;
		dm_block_t b = value64(n, 0);

		r = dm_tm_read_lock(info->tm, b, &btree_node_validator, &child);
		if (r)
			return r;

		memcpy(n, dm_block_data(child),
		       dm_bm_block_size(dm_tm_get_bm(info->tm)));
		r = dm_tm_unlock(info->tm, child);
		if (r)
			return r;

		dm_tm_dec(info->tm, dm_block_location(child));
		return 0;
	}

	i = lower_bound(n, key);
	if (i < 0)
		return -ENODATA;

	r = get_nr_entries(info->tm, value64(n, i), &child_entries);
	if (r)
		return r;

	has_left_sibling = i > 0;
	has_right_sibling = i < (le32_to_cpu(n->header.nr_entries) - 1);

	if (!has_left_sibling)
		r = rebalance2(s, info, vt, i);

	else if (!has_right_sibling)
		r = rebalance2(s, info, vt, i - 1);

	else
		r = rebalance3(s, info, vt, i - 1);

	return r;
}