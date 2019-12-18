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
typedef  scalar_t__ u64 ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct btrfs_fs_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_panic (struct btrfs_fs_info*,int,char*,unsigned long long) ; 
 struct btrfs_fs_info* btrfs_sb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ordered_data_tree_panic(struct inode *inode, int errno,
					       u64 offset)
{
	struct btrfs_fs_info *fs_info = btrfs_sb(inode->i_sb);
	btrfs_panic(fs_info, errno, "Inconsistency in ordered tree at offset "
		    "%llu\n", (unsigned long long)offset);
}