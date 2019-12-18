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
typedef  int /*<<< orphan*/  u64 ;
typedef  int /*<<< orphan*/  u32 ;
struct extent_buffer {scalar_t__ len; scalar_t__ start; int /*<<< orphan*/  bflags; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  blocks_used; TYPE_2__* transaction; int /*<<< orphan*/  transid; } ;
struct TYPE_3__ {scalar_t__ objectid; } ;
struct btrfs_root {int log_transid; int /*<<< orphan*/  dirty_log_pages; TYPE_1__ root_key; } ;
struct TYPE_4__ {int /*<<< orphan*/  dirty_pages; } ;

/* Variables and functions */
 scalar_t__ BTRFS_TREE_LOG_OBJECTID ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct extent_buffer* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  EXTENT_BUFFER_STALE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct extent_buffer* btrfs_find_create_tree_block (struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_buffer_lockdep_class (scalar_t__,struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_buffer_uptodate (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_header_generation (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_lock_blocking (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_tree_lock (struct extent_buffer*) ; 
 int /*<<< orphan*/  clean_tree_block (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_extent_dirty (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_extent_new (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

struct extent_buffer *btrfs_init_new_buffer(struct btrfs_trans_handle *trans,
					    struct btrfs_root *root,
					    u64 bytenr, u32 blocksize,
					    int level)
{
	struct extent_buffer *buf;

	buf = btrfs_find_create_tree_block(root, bytenr, blocksize);
	if (!buf)
		return ERR_PTR(-ENOMEM);
	btrfs_set_header_generation(buf, trans->transid);
	btrfs_set_buffer_lockdep_class(root->root_key.objectid, buf, level);
	btrfs_tree_lock(buf);
	clean_tree_block(trans, root, buf);
	clear_bit(EXTENT_BUFFER_STALE, &buf->bflags);

	btrfs_set_lock_blocking(buf);
	btrfs_set_buffer_uptodate(buf);

	if (root->root_key.objectid == BTRFS_TREE_LOG_OBJECTID) {
		/*
		 * we allow two log transactions at a time, use different
		 * EXENT bit to differentiate dirty pages.
		 */
		if (root->log_transid % 2 == 0)
			set_extent_dirty(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1, GFP_NOFS);
		else
			set_extent_new(&root->dirty_log_pages, buf->start,
					buf->start + buf->len - 1, GFP_NOFS);
	} else {
		set_extent_dirty(&trans->transaction->dirty_pages, buf->start,
			 buf->start + buf->len - 1, GFP_NOFS);
	}
	trans->blocks_used++;
	/* this returns a buffer locked for blocking */
	return buf;
}