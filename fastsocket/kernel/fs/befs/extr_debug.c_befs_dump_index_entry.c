#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  max_size; int /*<<< orphan*/  free_node_ptr; int /*<<< orphan*/  root_node_ptr; int /*<<< orphan*/  data_type; int /*<<< orphan*/  max_depth; int /*<<< orphan*/  node_size; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ befs_disk_btree_super ;

/* Variables and functions */
 int /*<<< orphan*/  befs_debug (struct super_block const*,char*,...) ; 
 int /*<<< orphan*/  fs32_to_cpu (struct super_block const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fs64_to_cpu (struct super_block const*,int /*<<< orphan*/ ) ; 

void
befs_dump_index_entry(const struct super_block *sb, befs_disk_btree_super * super)
{
#ifdef CONFIG_BEFS_DEBUG

	befs_debug(sb, "Btree super structure");
	befs_debug(sb, "  magic %08x", fs32_to_cpu(sb, super->magic));
	befs_debug(sb, "  node_size %u", fs32_to_cpu(sb, super->node_size));
	befs_debug(sb, "  max_depth %08x", fs32_to_cpu(sb, super->max_depth));

	befs_debug(sb, "  data_type %08x", fs32_to_cpu(sb, super->data_type));
	befs_debug(sb, "  root_node_pointer %016LX",
		   fs64_to_cpu(sb, super->root_node_ptr));
	befs_debug(sb, "  free_node_pointer %016LX",
		   fs64_to_cpu(sb, super->free_node_ptr));
	befs_debug(sb, "  maximum size %016LX",
		   fs64_to_cpu(sb, super->max_size));

#endif				//CONFIG_BEFS_DEBUG
}