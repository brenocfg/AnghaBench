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
struct btrfs_mapping_tree {int dummy; } ;
struct btrfs_bio {int dummy; } ;

/* Variables and functions */
 int __btrfs_map_block (struct btrfs_mapping_tree*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct btrfs_bio**,int) ; 

int btrfs_map_block(struct btrfs_mapping_tree *map_tree, int rw,
		      u64 logical, u64 *length,
		      struct btrfs_bio **bbio_ret, int mirror_num)
{
	return __btrfs_map_block(map_tree, rw, logical, length, bbio_ret,
				 mirror_num);
}