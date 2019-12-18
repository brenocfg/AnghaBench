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
typedef  int /*<<< orphan*/  u64 ;
struct walk_control {int free; int /*<<< orphan*/  process_func; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int /*<<< orphan*/  node; int /*<<< orphan*/  dirty_log_pages; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int EXTENT_DIRTY ; 
 int EXTENT_NEW ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  clear_extent_bits (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int find_first_extent_bit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_extent_buffer (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct btrfs_root*) ; 
 int /*<<< orphan*/  process_one_buffer ; 
 int walk_log_tree (struct btrfs_trans_handle*,struct btrfs_root*,struct walk_control*) ; 

__attribute__((used)) static void free_log_tree(struct btrfs_trans_handle *trans,
			  struct btrfs_root *log)
{
	int ret;
	u64 start;
	u64 end;
	struct walk_control wc = {
		.free = 1,
		.process_func = process_one_buffer
	};

	ret = walk_log_tree(trans, log, &wc);
	BUG_ON(ret);

	while (1) {
		ret = find_first_extent_bit(&log->dirty_log_pages,
				0, &start, &end, EXTENT_DIRTY | EXTENT_NEW);
		if (ret)
			break;

		clear_extent_bits(&log->dirty_log_pages, start, end,
				  EXTENT_DIRTY | EXTENT_NEW, GFP_NOFS);
	}

	free_extent_buffer(log->node);
	kfree(log);
}