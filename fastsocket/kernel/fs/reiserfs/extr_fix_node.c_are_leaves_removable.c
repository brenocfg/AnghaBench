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
struct virtual_node {int vn_nr_item; int vn_size; TYPE_1__* vn_vi; } ;
struct tree_balance {int /*<<< orphan*/  tb_sb; int /*<<< orphan*/ * rkey; scalar_t__* CFR; int /*<<< orphan*/  tb_path; struct virtual_node* tb_vn; } ;
struct item_head {int /*<<< orphan*/  ih_key; } ;
struct buffer_head {int dummy; } ;
struct TYPE_2__ {int vi_type; } ;

/* Variables and functions */
 int B_NR_ITEMS (struct buffer_head*) ; 
 int /*<<< orphan*/  B_N_PDELIM_KEY (scalar_t__,int /*<<< orphan*/ ) ; 
 struct item_head* B_N_PITEM_HEAD (struct buffer_head*,int /*<<< orphan*/ ) ; 
 scalar_t__ DOT_OFFSET ; 
 int IH_SIZE ; 
 int MAX_CHILD_SIZE (struct buffer_head*) ; 
 struct buffer_head* PATH_H_PBUFFER (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROC_INFO_INC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RFALSE (int,char*,...) ; 
 int VI_TYPE_LEFT_MERGEABLE ; 
 int VI_TYPE_RIGHT_MERGEABLE ; 
 int /*<<< orphan*/  comp_short_le_keys (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ is_direntry_le_ih (struct item_head*) ; 
 scalar_t__ le_ih_k_offset (struct item_head*) ; 
 int /*<<< orphan*/  leaves_removable ; 
 int /*<<< orphan*/  set_parameters (struct tree_balance*,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ *,int,int) ; 

__attribute__((used)) static int are_leaves_removable(struct tree_balance *tb, int lfree, int rfree)
{
	struct virtual_node *vn = tb->tb_vn;
	int ih_size;
	struct buffer_head *S0;

	S0 = PATH_H_PBUFFER(tb->tb_path, 0);

	ih_size = 0;
	if (vn->vn_nr_item) {
		if (vn->vn_vi[0].vi_type & VI_TYPE_LEFT_MERGEABLE)
			ih_size += IH_SIZE;

		if (vn->vn_vi[vn->vn_nr_item - 1].
		    vi_type & VI_TYPE_RIGHT_MERGEABLE)
			ih_size += IH_SIZE;
	} else {
		/* there was only one item and it will be deleted */
		struct item_head *ih;

		RFALSE(B_NR_ITEMS(S0) != 1,
		       "vs-8125: item number must be 1: it is %d",
		       B_NR_ITEMS(S0));

		ih = B_N_PITEM_HEAD(S0, 0);
		if (tb->CFR[0]
		    && !comp_short_le_keys(&(ih->ih_key),
					   B_N_PDELIM_KEY(tb->CFR[0],
							  tb->rkey[0])))
			if (is_direntry_le_ih(ih)) {
				/* Directory must be in correct state here: that is
				   somewhere at the left side should exist first directory
				   item. But the item being deleted can not be that first
				   one because its right neighbor is item of the same
				   directory. (But first item always gets deleted in last
				   turn). So, neighbors of deleted item can be merged, so
				   we can save ih_size */
				ih_size = IH_SIZE;

				/* we might check that left neighbor exists and is of the
				   same directory */
				RFALSE(le_ih_k_offset(ih) == DOT_OFFSET,
				       "vs-8130: first directory item can not be removed until directory is not empty");
			}

	}

	if (MAX_CHILD_SIZE(S0) + vn->vn_size <= rfree + lfree + ih_size) {
		set_parameters(tb, 0, -1, -1, -1, NULL, -1, -1);
		PROC_INFO_INC(tb->tb_sb, leaves_removable);
		return 1;
	}
	return 0;

}