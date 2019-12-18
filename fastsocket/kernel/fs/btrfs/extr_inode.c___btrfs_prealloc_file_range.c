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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_ctime; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {scalar_t__ objectid; scalar_t__ offset; } ;
typedef  scalar_t__ loff_t ;
struct TYPE_2__ {int /*<<< orphan*/  flags; struct btrfs_root* root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BTRFS_FILE_EXTENT_PREALLOC ; 
 TYPE_1__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  BTRFS_INODE_PREALLOC ; 
 int /*<<< orphan*/  CURRENT_TIME ; 
 int FALLOC_FL_KEEP_SIZE ; 
 scalar_t__ IS_ERR (struct btrfs_trans_handle*) ; 
 int PTR_ERR (struct btrfs_trans_handle*) ; 
 int /*<<< orphan*/  btrfs_abort_transaction (struct btrfs_trans_handle*,struct btrfs_root*,int) ; 
 int /*<<< orphan*/  btrfs_drop_extent_cache (struct inode*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_end_transaction (struct btrfs_trans_handle*,struct btrfs_root*) ; 
 int /*<<< orphan*/  btrfs_ordered_update_i_size (struct inode*,scalar_t__,int /*<<< orphan*/ *) ; 
 int btrfs_reserve_extent (struct btrfs_trans_handle*,struct btrfs_root*,scalar_t__,scalar_t__,int /*<<< orphan*/ ,scalar_t__,struct btrfs_key*,int) ; 
 struct btrfs_trans_handle* btrfs_start_transaction (struct btrfs_root*,int) ; 
 int btrfs_update_inode (struct btrfs_trans_handle*,struct btrfs_root*,struct inode*) ; 
 int /*<<< orphan*/  i_size_write (struct inode*,scalar_t__) ; 
 int /*<<< orphan*/  inode_inc_iversion (struct inode*) ; 
 int insert_reserved_file_extent (struct btrfs_trans_handle*,struct inode*,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __btrfs_prealloc_file_range(struct inode *inode, int mode,
				       u64 start, u64 num_bytes, u64 min_size,
				       loff_t actual_len, u64 *alloc_hint,
				       struct btrfs_trans_handle *trans)
{
	struct btrfs_root *root = BTRFS_I(inode)->root;
	struct btrfs_key ins;
	u64 cur_offset = start;
	u64 i_size;
	int ret = 0;
	bool own_trans = true;

	if (trans)
		own_trans = false;
	while (num_bytes > 0) {
		if (own_trans) {
			trans = btrfs_start_transaction(root, 3);
			if (IS_ERR(trans)) {
				ret = PTR_ERR(trans);
				break;
			}
		}

		ret = btrfs_reserve_extent(trans, root, num_bytes, min_size,
					   0, *alloc_hint, &ins, 1);
		if (ret) {
			if (own_trans)
				btrfs_end_transaction(trans, root);
			break;
		}

		ret = insert_reserved_file_extent(trans, inode,
						  cur_offset, ins.objectid,
						  ins.offset, ins.offset,
						  ins.offset, 0, 0, 0,
						  BTRFS_FILE_EXTENT_PREALLOC);
		if (ret) {
			btrfs_abort_transaction(trans, root, ret);
			if (own_trans)
				btrfs_end_transaction(trans, root);
			break;
		}
		btrfs_drop_extent_cache(inode, cur_offset,
					cur_offset + ins.offset -1, 0);

		num_bytes -= ins.offset;
		cur_offset += ins.offset;
		*alloc_hint = ins.objectid + ins.offset;

		inode_inc_iversion(inode);
		inode->i_ctime = CURRENT_TIME;
		BTRFS_I(inode)->flags |= BTRFS_INODE_PREALLOC;
		if (!(mode & FALLOC_FL_KEEP_SIZE) &&
		    (actual_len > inode->i_size) &&
		    (cur_offset > inode->i_size)) {
			if (cur_offset > actual_len)
				i_size = actual_len;
			else
				i_size = cur_offset;
			i_size_write(inode, i_size);
			btrfs_ordered_update_i_size(inode, i_size, NULL);
		}

		ret = btrfs_update_inode(trans, root, inode);

		if (ret) {
			btrfs_abort_transaction(trans, root, ret);
			if (own_trans)
				btrfs_end_transaction(trans, root);
			break;
		}

		if (own_trans)
			btrfs_end_transaction(trans, root);
	}
	return ret;
}