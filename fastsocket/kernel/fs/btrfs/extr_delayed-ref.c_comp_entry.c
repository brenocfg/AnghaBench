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
struct btrfs_delayed_ref_node {scalar_t__ bytenr; scalar_t__ type; scalar_t__ seq; scalar_t__ is_head; } ;

/* Variables and functions */
 scalar_t__ BTRFS_EXTENT_DATA_REF_KEY ; 
 scalar_t__ BTRFS_SHARED_BLOCK_REF_KEY ; 
 scalar_t__ BTRFS_SHARED_DATA_REF_KEY ; 
 scalar_t__ BTRFS_TREE_BLOCK_REF_KEY ; 
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  btrfs_delayed_node_to_data_ref (struct btrfs_delayed_ref_node*) ; 
 int /*<<< orphan*/  btrfs_delayed_node_to_tree_ref (struct btrfs_delayed_ref_node*) ; 
 int comp_data_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int comp_tree_refs (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int comp_entry(struct btrfs_delayed_ref_node *ref2,
		      struct btrfs_delayed_ref_node *ref1)
{
	if (ref1->bytenr < ref2->bytenr)
		return -1;
	if (ref1->bytenr > ref2->bytenr)
		return 1;
	if (ref1->is_head && ref2->is_head)
		return 0;
	if (ref2->is_head)
		return -1;
	if (ref1->is_head)
		return 1;
	if (ref1->type < ref2->type)
		return -1;
	if (ref1->type > ref2->type)
		return 1;
	/* merging of sequenced refs is not allowed */
	if (ref1->seq < ref2->seq)
		return -1;
	if (ref1->seq > ref2->seq)
		return 1;
	if (ref1->type == BTRFS_TREE_BLOCK_REF_KEY ||
	    ref1->type == BTRFS_SHARED_BLOCK_REF_KEY) {
		return comp_tree_refs(btrfs_delayed_node_to_tree_ref(ref2),
				      btrfs_delayed_node_to_tree_ref(ref1));
	} else if (ref1->type == BTRFS_EXTENT_DATA_REF_KEY ||
		   ref1->type == BTRFS_SHARED_DATA_REF_KEY) {
		return comp_data_refs(btrfs_delayed_node_to_data_ref(ref2),
				      btrfs_delayed_node_to_data_ref(ref1));
	}
	BUG();
	return 0;
}