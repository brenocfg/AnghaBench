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
struct btrfs_fs_info {int /*<<< orphan*/  tree_root; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int del_balance_item (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unset_balance_control (struct btrfs_fs_info*) ; 

__attribute__((used)) static void __cancel_balance(struct btrfs_fs_info *fs_info)
{
	int ret;

	unset_balance_control(fs_info);
	ret = del_balance_item(fs_info->tree_root);
	BUG_ON(ret);
}