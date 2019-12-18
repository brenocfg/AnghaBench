#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct super_block {int dummy; } ;
typedef  int /*<<< orphan*/  befs_off_t ;
typedef  int /*<<< orphan*/  befs_data_stream ;
struct TYPE_9__ {int /*<<< orphan*/  all_key_length; int /*<<< orphan*/  all_key_count; int /*<<< orphan*/  overflow; int /*<<< orphan*/  right; int /*<<< orphan*/  left; } ;
typedef  TYPE_2__ befs_btree_nodehead ;
struct TYPE_8__ {void* all_key_length; void* all_key_count; void* overflow; void* right; void* left; } ;
struct TYPE_10__ {TYPE_2__* od_node; TYPE_1__ head; TYPE_4__* bh; } ;
typedef  TYPE_3__ befs_btree_node ;
struct TYPE_11__ {scalar_t__ b_data; } ;

/* Variables and functions */
 int BEFS_ERR ; 
 int BEFS_OK ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*) ; 
 int /*<<< orphan*/  befs_dump_index_node (struct super_block*,TYPE_2__*) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*,int /*<<< orphan*/ ) ; 
 TYPE_4__* befs_read_datastream (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  brelse (TYPE_4__*) ; 
 void* fs16_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
befs_bt_read_node(struct super_block *sb, befs_data_stream * ds,
		  befs_btree_node * node, befs_off_t node_off)
{
	uint off = 0;

	befs_debug(sb, "---> befs_bt_read_node()");

	if (node->bh)
		brelse(node->bh);

	node->bh = befs_read_datastream(sb, ds, node_off, &off);
	if (!node->bh) {
		befs_error(sb, "befs_bt_read_node() failed to read "
			   "node at %Lu", node_off);
		befs_debug(sb, "<--- befs_bt_read_node() ERROR");

		return BEFS_ERR;
	}
	node->od_node =
	    (befs_btree_nodehead *) ((void *) node->bh->b_data + off);

	befs_dump_index_node(sb, node->od_node);

	node->head.left = fs64_to_cpu(sb, node->od_node->left);
	node->head.right = fs64_to_cpu(sb, node->od_node->right);
	node->head.overflow = fs64_to_cpu(sb, node->od_node->overflow);
	node->head.all_key_count =
	    fs16_to_cpu(sb, node->od_node->all_key_count);
	node->head.all_key_length =
	    fs16_to_cpu(sb, node->od_node->all_key_length);

	befs_debug(sb, "<--- befs_btree_read_node()");
	return BEFS_OK;
}