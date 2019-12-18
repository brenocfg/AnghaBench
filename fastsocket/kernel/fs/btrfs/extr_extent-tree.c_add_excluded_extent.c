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
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_2__ {int /*<<< orphan*/ * freed_extents; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXTENT_UPTODATE ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  set_extent_bits (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int add_excluded_extent(struct btrfs_root *root,
			       u64 start, u64 num_bytes)
{
	u64 end = start + num_bytes - 1;
	set_extent_bits(&root->fs_info->freed_extents[0],
			start, end, EXTENT_UPTODATE, GFP_NOFS);
	set_extent_bits(&root->fs_info->freed_extents[1],
			start, end, EXTENT_UPTODATE, GFP_NOFS);
	return 0;
}