#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct buffer_head {scalar_t__ b_data; } ;
struct TYPE_5__ {int /*<<< orphan*/  max_size; int /*<<< orphan*/  free_node_ptr; int /*<<< orphan*/  root_node_ptr; int /*<<< orphan*/  data_type; int /*<<< orphan*/  max_depth; int /*<<< orphan*/  node_size; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ befs_disk_btree_super ;
typedef  int /*<<< orphan*/  befs_data_stream ;
struct TYPE_6__ {void* magic; void* max_size; void* free_node_ptr; void* root_node_ptr; void* data_type; void* max_depth; void* node_size; } ;
typedef  TYPE_2__ befs_btree_super ;

/* Variables and functions */
 void* BEFS_BTREE_MAGIC ; 
 int BEFS_ERR ; 
 int BEFS_OK ; 
 int /*<<< orphan*/  befs_debug (struct super_block*,char*) ; 
 int /*<<< orphan*/  befs_dump_index_entry (struct super_block*,TYPE_1__*) ; 
 int /*<<< orphan*/  befs_error (struct super_block*,char*) ; 
 struct buffer_head* befs_read_datastream (struct super_block*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 void* fs32_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 
 void* fs64_to_cpu (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
befs_bt_read_super(struct super_block *sb, befs_data_stream * ds,
		   befs_btree_super * sup)
{
	struct buffer_head *bh = NULL;
	befs_disk_btree_super *od_sup = NULL;

	befs_debug(sb, "---> befs_btree_read_super()");

	bh = befs_read_datastream(sb, ds, 0, NULL);

	if (!bh) {
		befs_error(sb, "Couldn't read index header.");
		goto error;
	}
	od_sup = (befs_disk_btree_super *) bh->b_data;
	befs_dump_index_entry(sb, od_sup);

	sup->magic = fs32_to_cpu(sb, od_sup->magic);
	sup->node_size = fs32_to_cpu(sb, od_sup->node_size);
	sup->max_depth = fs32_to_cpu(sb, od_sup->max_depth);
	sup->data_type = fs32_to_cpu(sb, od_sup->data_type);
	sup->root_node_ptr = fs64_to_cpu(sb, od_sup->root_node_ptr);
	sup->free_node_ptr = fs64_to_cpu(sb, od_sup->free_node_ptr);
	sup->max_size = fs64_to_cpu(sb, od_sup->max_size);

	brelse(bh);
	if (sup->magic != BEFS_BTREE_MAGIC) {
		befs_error(sb, "Index header has bad magic.");
		goto error;
	}

	befs_debug(sb, "<--- befs_btree_read_super()");
	return BEFS_OK;

      error:
	befs_debug(sb, "<--- befs_btree_read_super() ERROR");
	return BEFS_ERR;
}