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
struct btrfs_key {int dummy; } ;
struct btrfs_disk_key {int dummy; } ;
struct btrfs_dir_item {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  btrfs_dir_item_key (struct extent_buffer*,struct btrfs_dir_item*,struct btrfs_disk_key*) ; 
 int /*<<< orphan*/  btrfs_disk_key_to_cpu (struct btrfs_key*,struct btrfs_disk_key*) ; 

__attribute__((used)) static inline void btrfs_dir_item_key_to_cpu(struct extent_buffer *eb,
				      struct btrfs_dir_item *item,
				      struct btrfs_key *key)
{
	struct btrfs_disk_key disk_key;
	btrfs_dir_item_key(eb, item, &disk_key);
	btrfs_disk_key_to_cpu(key, &disk_key);
}