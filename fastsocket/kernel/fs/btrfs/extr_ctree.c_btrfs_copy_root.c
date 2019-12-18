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
struct extent_buffer {int /*<<< orphan*/  start; int /*<<< orphan*/  len; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_root {TYPE_2__* fs_info; int /*<<< orphan*/  last_trans; scalar_t__ ref_cows; } ;
struct btrfs_disk_key {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  fsid; TYPE_1__* running_transaction; } ;
struct TYPE_3__ {int /*<<< orphan*/  transid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FSID_SIZE ; 
 int BTRFS_HEADER_FLAG_RELOC ; 
 int BTRFS_HEADER_FLAG_WRITTEN ; 
 int /*<<< orphan*/  BTRFS_MIXED_BACKREF_REV ; 
 int /*<<< orphan*/  BTRFS_TREE_RELOC_OBJECTID ; 
 scalar_t__ IS_ERR (struct extent_buffer*) ; 
 int PTR_ERR (struct extent_buffer*) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 struct extent_buffer* btrfs_alloc_free_block (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct btrfs_disk_key*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_clear_header_flag (struct extent_buffer*,int) ; 
 scalar_t__ btrfs_header_fsid (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_header_generation (struct extent_buffer*) ; 
 int btrfs_header_level (struct extent_buffer*) ; 
 int btrfs_inc_ref (struct btrfs_trans_handle*,struct btrfs_root*,struct extent_buffer*,int,int) ; 
 int /*<<< orphan*/  btrfs_item_key (struct extent_buffer*,struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_node_key (struct extent_buffer*,struct btrfs_disk_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_backref_rev (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_bytenr (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_flag (struct extent_buffer*,int) ; 
 int /*<<< orphan*/  btrfs_set_header_generation (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_header_owner (struct extent_buffer*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  copy_extent_buffer (struct extent_buffer*,struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_extent_buffer (struct extent_buffer*,int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ) ; 

int btrfs_copy_root(struct btrfs_trans_handle *trans,
		      struct btrfs_root *root,
		      struct extent_buffer *buf,
		      struct extent_buffer **cow_ret, u64 new_root_objectid)
{
	struct extent_buffer *cow;
	int ret = 0;
	int level;
	struct btrfs_disk_key disk_key;

	WARN_ON(root->ref_cows && trans->transid !=
		root->fs_info->running_transaction->transid);
	WARN_ON(root->ref_cows && trans->transid != root->last_trans);

	level = btrfs_header_level(buf);
	if (level == 0)
		btrfs_item_key(buf, &disk_key, 0);
	else
		btrfs_node_key(buf, &disk_key, 0);

	cow = btrfs_alloc_free_block(trans, root, buf->len, 0,
				     new_root_objectid, &disk_key, level,
				     buf->start, 0);
	if (IS_ERR(cow))
		return PTR_ERR(cow);

	copy_extent_buffer(cow, buf, 0, 0, cow->len);
	btrfs_set_header_bytenr(cow, cow->start);
	btrfs_set_header_generation(cow, trans->transid);
	btrfs_set_header_backref_rev(cow, BTRFS_MIXED_BACKREF_REV);
	btrfs_clear_header_flag(cow, BTRFS_HEADER_FLAG_WRITTEN |
				     BTRFS_HEADER_FLAG_RELOC);
	if (new_root_objectid == BTRFS_TREE_RELOC_OBJECTID)
		btrfs_set_header_flag(cow, BTRFS_HEADER_FLAG_RELOC);
	else
		btrfs_set_header_owner(cow, new_root_objectid);

	write_extent_buffer(cow, root->fs_info->fsid,
			    (unsigned long)btrfs_header_fsid(cow),
			    BTRFS_FSID_SIZE);

	WARN_ON(btrfs_header_generation(buf) > trans->transid);
	if (new_root_objectid == BTRFS_TREE_RELOC_OBJECTID)
		ret = btrfs_inc_ref(trans, root, cow, 1, 1);
	else
		ret = btrfs_inc_ref(trans, root, cow, 0, 1);

	if (ret)
		return ret;

	btrfs_mark_buffer_dirty(cow);
	*cow_ret = cow;
	return 0;
}