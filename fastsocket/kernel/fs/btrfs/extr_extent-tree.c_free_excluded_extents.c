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
typedef  scalar_t__ u64 ;
struct btrfs_root {TYPE_2__* fs_info; } ;
struct TYPE_3__ {scalar_t__ offset; scalar_t__ objectid; } ;
struct btrfs_block_group_cache {TYPE_1__ key; } ;
struct TYPE_4__ {int /*<<< orphan*/ * freed_extents; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_UPTODATE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  clear_extent_bits (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_excluded_extents(struct btrfs_root *root,
				  struct btrfs_block_group_cache *cache)
{
	u64 start, end;

	start = cache->key.objectid;
	end = start + cache->key.offset - 1;

	clear_extent_bits(&root->fs_info->freed_extents[0],
			  start, end, EXTENT_UPTODATE, GFP_NOFS);
	clear_extent_bits(&root->fs_info->freed_extents[1],
			  start, end, EXTENT_UPTODATE, GFP_NOFS);
}