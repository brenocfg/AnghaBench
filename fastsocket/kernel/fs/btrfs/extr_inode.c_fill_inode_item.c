#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_6__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct TYPE_5__ {int /*<<< orphan*/  tv_nsec; int /*<<< orphan*/  tv_sec; } ;
struct inode {int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_version; TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_inode_item {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  generation; int /*<<< orphan*/  disk_i_size; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_inode_atime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_inode_ctime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_inode_mtime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_set_inode_block_group (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_flags (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_generation (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_gid (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_mode (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_nbytes (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_nlink (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_rdev (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_sequence (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_size (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_transid (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_inode_uid (struct extent_buffer*,struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_timespec_nsec (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_timespec_sec (struct extent_buffer*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_get_bytes (struct inode*) ; 

__attribute__((used)) static void fill_inode_item(struct btrfs_trans_handle *trans,
			    struct extent_buffer *leaf,
			    struct btrfs_inode_item *item,
			    struct inode *inode)
{
	btrfs_set_inode_uid(leaf, item, inode->i_uid);
	btrfs_set_inode_gid(leaf, item, inode->i_gid);
	btrfs_set_inode_size(leaf, item, BTRFS_I(inode)->disk_i_size);
	btrfs_set_inode_mode(leaf, item, inode->i_mode);
	btrfs_set_inode_nlink(leaf, item, inode->i_nlink);

	btrfs_set_timespec_sec(leaf, btrfs_inode_atime(item),
			       inode->i_atime.tv_sec);
	btrfs_set_timespec_nsec(leaf, btrfs_inode_atime(item),
				inode->i_atime.tv_nsec);

	btrfs_set_timespec_sec(leaf, btrfs_inode_mtime(item),
			       inode->i_mtime.tv_sec);
	btrfs_set_timespec_nsec(leaf, btrfs_inode_mtime(item),
				inode->i_mtime.tv_nsec);

	btrfs_set_timespec_sec(leaf, btrfs_inode_ctime(item),
			       inode->i_ctime.tv_sec);
	btrfs_set_timespec_nsec(leaf, btrfs_inode_ctime(item),
				inode->i_ctime.tv_nsec);

	btrfs_set_inode_nbytes(leaf, item, inode_get_bytes(inode));
	btrfs_set_inode_generation(leaf, item, BTRFS_I(inode)->generation);
	btrfs_set_inode_sequence(leaf, item, inode->i_version);
	btrfs_set_inode_transid(leaf, item, trans->transid);
	btrfs_set_inode_rdev(leaf, item, inode->i_rdev);
	btrfs_set_inode_flags(leaf, item, BTRFS_I(inode)->flags);
	btrfs_set_inode_block_group(leaf, item, 0);
}