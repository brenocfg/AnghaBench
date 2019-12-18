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
typedef  int /*<<< orphan*/  u64 ;
struct walk_control {scalar_t__ wait; scalar_t__ write; int /*<<< orphan*/  trans; scalar_t__ pin; } ;
struct extent_buffer {int /*<<< orphan*/  len; int /*<<< orphan*/  start; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/  extent_root; } ;

/* Variables and functions */
 scalar_t__ btrfs_buffer_uptodate (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_pin_extent_for_log_replay (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_wait_tree_block_writeback (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_write_tree_block (struct extent_buffer*) ; 

__attribute__((used)) static int process_one_buffer(struct btrfs_root *log,
			      struct extent_buffer *eb,
			      struct walk_control *wc, u64 gen)
{
	if (wc->pin)
		btrfs_pin_extent_for_log_replay(wc->trans,
						log->fs_info->extent_root,
						eb->start, eb->len);

	if (btrfs_buffer_uptodate(eb, gen, 0)) {
		if (wc->write)
			btrfs_write_tree_block(eb);
		if (wc->wait)
			btrfs_wait_tree_block_writeback(eb);
	}
	return 0;
}