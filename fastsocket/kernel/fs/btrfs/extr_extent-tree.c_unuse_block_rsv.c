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
typedef  int /*<<< orphan*/  u32 ;
struct btrfs_fs_info {int dummy; } ;
struct btrfs_block_rsv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_rsv_add_bytes (struct btrfs_block_rsv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_rsv_release_bytes (struct btrfs_fs_info*,struct btrfs_block_rsv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void unuse_block_rsv(struct btrfs_fs_info *fs_info,
			    struct btrfs_block_rsv *block_rsv, u32 blocksize)
{
	block_rsv_add_bytes(block_rsv, blocksize, 0);
	block_rsv_release_bytes(fs_info, block_rsv, NULL, 0);
}