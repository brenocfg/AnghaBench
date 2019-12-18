#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u32 ;
struct super_block {int dummy; } ;
struct hfsplus_fork_raw {TYPE_3__* extents; int /*<<< orphan*/  total_blocks; } ;
struct hfs_find_data {TYPE_2__* key; } ;
typedef  TYPE_3__* hfsplus_extent_rec ;
struct TYPE_10__ {int /*<<< orphan*/  ext_tree; } ;
struct TYPE_9__ {int /*<<< orphan*/  block_count; } ;
struct TYPE_7__ {int /*<<< orphan*/  start_block; } ;
struct TYPE_8__ {TYPE_1__ ext; } ;

/* Variables and functions */
 TYPE_6__ HFSPLUS_SB (struct super_block*) ; 
 int __hfsplus_ext_read_extent (struct hfs_find_data*,TYPE_3__*,scalar_t__,scalar_t__,int) ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hfs_brec_remove (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_exit (struct hfs_find_data*) ; 
 int /*<<< orphan*/  hfs_find_init (int /*<<< orphan*/ ,struct hfs_find_data*) ; 
 int hfsplus_free_extents (struct super_block*,TYPE_3__*,scalar_t__,scalar_t__) ; 

int hfsplus_free_fork(struct super_block *sb, u32 cnid, struct hfsplus_fork_raw *fork, int type)
{
	struct hfs_find_data fd;
	hfsplus_extent_rec ext_entry;
	u32 total_blocks, blocks, start;
	int res, i;

	total_blocks = be32_to_cpu(fork->total_blocks);
	if (!total_blocks)
		return 0;

	blocks = 0;
	for (i = 0; i < 8; i++)
		blocks += be32_to_cpu(fork->extents[i].block_count);

	res = hfsplus_free_extents(sb, fork->extents, blocks, blocks);
	if (res)
		return res;
	if (total_blocks == blocks)
		return 0;

	hfs_find_init(HFSPLUS_SB(sb).ext_tree, &fd);
	do {
		res = __hfsplus_ext_read_extent(&fd, ext_entry, cnid,
						total_blocks, type);
		if (res)
			break;
		start = be32_to_cpu(fd.key->ext.start_block);
		hfsplus_free_extents(sb, ext_entry,
				     total_blocks - start,
				     total_blocks);
		hfs_brec_remove(&fd);
		total_blocks = start;
	} while (total_blocks > blocks);
	hfs_find_exit(&fd);

	return res;
}