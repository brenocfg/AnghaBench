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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;

/* Variables and functions */
 int btrfs_find_orphan_item (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int btrfs_insert_orphan_item (struct btrfs_trans_handle*,struct btrfs_root*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int insert_orphan_item(struct btrfs_trans_handle *trans,
			      struct btrfs_root *root, u64 offset)
{
	int ret;
	ret = btrfs_find_orphan_item(root, offset);
	if (ret > 0)
		ret = btrfs_insert_orphan_item(trans, root, offset);
	return ret;
}