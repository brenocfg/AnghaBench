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
struct extent_buffer {int dummy; } ;
struct btrfs_trans_handle {int dummy; } ;
struct btrfs_root {int dummy; } ;
struct btrfs_path {int* slots; struct extent_buffer** nodes; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  btrfs_cpu_key_to_disk (struct btrfs_disk_key*,struct btrfs_key*) ; 
 int btrfs_header_nritems (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_item_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 int /*<<< orphan*/  btrfs_mark_buffer_dirty (struct extent_buffer*) ; 
 int /*<<< orphan*/  btrfs_set_item_key (struct extent_buffer*,struct btrfs_disk_key*,int) ; 
 scalar_t__ comp_keys (struct btrfs_disk_key*,struct btrfs_key*) ; 
 int /*<<< orphan*/  fixup_low_keys (struct btrfs_trans_handle*,struct btrfs_root*,struct btrfs_path*,struct btrfs_disk_key*,int) ; 

void btrfs_set_item_key_safe(struct btrfs_trans_handle *trans,
			     struct btrfs_root *root, struct btrfs_path *path,
			     struct btrfs_key *new_key)
{
	struct btrfs_disk_key disk_key;
	struct extent_buffer *eb;
	int slot;

	eb = path->nodes[0];
	slot = path->slots[0];
	if (slot > 0) {
		btrfs_item_key(eb, &disk_key, slot - 1);
		BUG_ON(comp_keys(&disk_key, new_key) >= 0);
	}
	if (slot < btrfs_header_nritems(eb) - 1) {
		btrfs_item_key(eb, &disk_key, slot + 1);
		BUG_ON(comp_keys(&disk_key, new_key) <= 0);
	}

	btrfs_cpu_key_to_disk(&disk_key, new_key);
	btrfs_set_item_key(eb, &disk_key, slot);
	btrfs_mark_buffer_dirty(eb);
	if (slot == 0)
		fixup_low_keys(trans, root, path, &disk_key, 1);
}