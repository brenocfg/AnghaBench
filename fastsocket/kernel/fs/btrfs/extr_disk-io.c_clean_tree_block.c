#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct extent_buffer {scalar_t__ len; int /*<<< orphan*/  bflags; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct TYPE_4__ {scalar_t__ dirty_metadata_bytes; int /*<<< orphan*/  delalloc_lock; TYPE_1__* running_transaction; } ;
struct TYPE_3__ {scalar_t__ transid; } ;

/* Variables and functions */
 int /*<<< orphan*/  EOVERFLOW ; 
 int /*<<< orphan*/  EXTENT_BUFFER_DIRTY ; 
 int /*<<< orphan*/  btrfs_assert_tree_locked (struct extent_buffer*) ; 
 scalar_t__ btrfs_header_generation (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_panic (TYPE_2__*,int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_extent_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void clean_tree_block(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		      struct extent_buffer *buf)
{
	if (btrfs_header_generation(buf) ==
	    root->fs_info->running_transaction->transid) {
		btrfs_assert_tree_locked(buf);

		if (test_and_clear_bit(EXTENT_BUFFER_DIRTY, &buf->bflags)) {
			spin_lock(&root->fs_info->delalloc_lock);
			if (root->fs_info->dirty_metadata_bytes >= buf->len)
				root->fs_info->dirty_metadata_bytes -= buf->len;
			else {
				spin_unlock(&root->fs_info->delalloc_lock);
				btrfs_panic(root->fs_info, -EOVERFLOW,
					  "Can't clear %lu bytes from "
					  " dirty_mdatadata_bytes (%lu)",
					  buf->len,
					  root->fs_info->dirty_metadata_bytes);
			}
			spin_unlock(&root->fs_info->delalloc_lock);
		}

		/* ugh, clear_extent_buffer_dirty needs to lock the page */
		btrfs_set_lock_blocking(buf);
		clear_extent_buffer_dirty(buf);
	}
}