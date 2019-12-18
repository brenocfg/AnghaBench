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
typedef  scalar_t__ u64 ;
struct map_lookup {int type; int num_stripes; int sub_stripes; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {scalar_t__ start; scalar_t__ len; scalar_t__ bdev; } ;
struct btrfs_mapping_tree {struct extent_map_tree map_tree; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_DUP ; 
 int BTRFS_BLOCK_GROUP_RAID1 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int btrfs_num_copies(struct btrfs_mapping_tree *map_tree, u64 logical, u64 len)
{
	struct extent_map *em;
	struct map_lookup *map;
	struct extent_map_tree *em_tree = &map_tree->map_tree;
	int ret;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, logical, len);
	read_unlock(&em_tree->lock);
	BUG_ON(!em);

	BUG_ON(em->start > logical || em->start + em->len < logical);
	map = (struct map_lookup *)em->bdev;
	if (map->type & (BTRFS_BLOCK_GROUP_DUP | BTRFS_BLOCK_GROUP_RAID1))
		ret = map->num_stripes;
	else if (map->type & BTRFS_BLOCK_GROUP_RAID10)
		ret = map->sub_stripes;
	else
		ret = 1;
	free_extent_map(em);
	return ret;
}