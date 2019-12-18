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
struct btrfs_root {int dummy; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_delayed_node {int /*<<< orphan*/  mutex; } ;
struct btrfs_delayed_item {int dummy; } ;

/* Variables and functions */
 struct btrfs_delayed_item* __btrfs_lookup_delayed_insertion_item (struct btrfs_delayed_node*,struct btrfs_key*) ; 
 int /*<<< orphan*/  btrfs_delayed_item_release_metadata (struct btrfs_root*,struct btrfs_delayed_item*) ; 
 int /*<<< orphan*/  btrfs_release_delayed_item (struct btrfs_delayed_item*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int btrfs_delete_delayed_insertion_item(struct btrfs_root *root,
					       struct btrfs_delayed_node *node,
					       struct btrfs_key *key)
{
	struct btrfs_delayed_item *item;

	mutex_lock(&node->mutex);
	item = __btrfs_lookup_delayed_insertion_item(node, key);
	if (!item) {
		mutex_unlock(&node->mutex);
		return 1;
	}

	btrfs_delayed_item_release_metadata(root, item);
	btrfs_release_delayed_item(item);
	mutex_unlock(&node->mutex);
	return 0;
}