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
struct inode {TYPE_3__ i_ctime; TYPE_2__ i_mtime; TYPE_1__ i_atime; int /*<<< orphan*/  i_rdev; int /*<<< orphan*/  i_version; int /*<<< orphan*/  i_nlink; int /*<<< orphan*/  i_mode; int /*<<< orphan*/  i_gid; int /*<<< orphan*/  i_uid; } ;
struct btrfs_trans_handle {int /*<<< orphan*/  transid; } ;
struct btrfs_inode_item {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  flags; int /*<<< orphan*/  generation; int /*<<< orphan*/  disk_i_size; } ;

/* Variables and functions */
 TYPE_4__* BTRFS_I (struct inode*) ; 
 int /*<<< orphan*/  btrfs_inode_atime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_inode_ctime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_inode_mtime (struct btrfs_inode_item*) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_block_group (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_flags (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_generation (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_gid (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_mode (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_nbytes (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_nlink (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_rdev (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_sequence (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_size (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_transid (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_inode_uid (struct btrfs_inode_item*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_timespec_nsec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btrfs_set_stack_timespec_sec (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inode_get_bytes (struct inode*) ; 

__attribute__((used)) static void fill_stack_inode_item(struct btrfs_trans_handle *trans,
				  struct btrfs_inode_item *inode_item,
				  struct inode *inode)
{
	btrfs_set_stack_inode_uid(inode_item, inode->i_uid);
	btrfs_set_stack_inode_gid(inode_item, inode->i_gid);
	btrfs_set_stack_inode_size(inode_item, BTRFS_I(inode)->disk_i_size);
	btrfs_set_stack_inode_mode(inode_item, inode->i_mode);
	btrfs_set_stack_inode_nlink(inode_item, inode->i_nlink);
	btrfs_set_stack_inode_nbytes(inode_item, inode_get_bytes(inode));
	btrfs_set_stack_inode_generation(inode_item,
					 BTRFS_I(inode)->generation);
	btrfs_set_stack_inode_sequence(inode_item, inode->i_version);
	btrfs_set_stack_inode_transid(inode_item, trans->transid);
	btrfs_set_stack_inode_rdev(inode_item, inode->i_rdev);
	btrfs_set_stack_inode_flags(inode_item, BTRFS_I(inode)->flags);
	btrfs_set_stack_inode_block_group(inode_item, 0);

	btrfs_set_stack_timespec_sec(btrfs_inode_atime(inode_item),
				     inode->i_atime.tv_sec);
	btrfs_set_stack_timespec_nsec(btrfs_inode_atime(inode_item),
				      inode->i_atime.tv_nsec);

	btrfs_set_stack_timespec_sec(btrfs_inode_mtime(inode_item),
				     inode->i_mtime.tv_sec);
	btrfs_set_stack_timespec_nsec(btrfs_inode_mtime(inode_item),
				      inode->i_mtime.tv_nsec);

	btrfs_set_stack_timespec_sec(btrfs_inode_ctime(inode_item),
				     inode->i_ctime.tv_sec);
	btrfs_set_stack_timespec_nsec(btrfs_inode_ctime(inode_item),
				      inode->i_ctime.tv_nsec);
}