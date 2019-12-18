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
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root_item {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_key {int dummy; } ;

/* Variables and functions */
 int btrfs_insert_item (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_key*,struct btrfs_root_item*,int) ; 

int btrfs_insert_root(struct btrfs_trans_handle *trans, struct btrfs_root *root,
		      struct btrfs_key *key, struct btrfs_root_item *item)
{
	return btrfs_insert_item(trans, root, key, item, sizeof(*item));
}