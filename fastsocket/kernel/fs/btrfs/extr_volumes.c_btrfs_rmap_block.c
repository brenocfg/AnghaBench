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
struct map_lookup {int type; int num_stripes; int sub_stripes; int stripe_len; TYPE_2__* stripes; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {scalar_t__ start; scalar_t__ len; scalar_t__ bdev; } ;
struct btrfs_mapping_tree {struct extent_map_tree map_tree; } ;
struct TYPE_4__ {scalar_t__ physical; TYPE_1__* dev; } ;
struct TYPE_3__ {scalar_t__ devid; } ;

/* Variables and functions */
 int BTRFS_BLOCK_GROUP_RAID0 ; 
 int BTRFS_BLOCK_GROUP_RAID10 ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  do_div (scalar_t__,int) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 scalar_t__* kzalloc (int,int /*<<< orphan*/ ) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int btrfs_rmap_block(struct btrfs_mapping_tree *map_tree,
		     u64 chunk_start, u64 physical, u64 devid,
		     u64 **logical, int *naddrs, int *stripe_len)
{
	struct extent_map_tree *em_tree = &map_tree->map_tree;
	struct extent_map *em;
	struct map_lookup *map;
	u64 *buf;
	u64 bytenr;
	u64 length;
	u64 stripe_nr;
	int i, j, nr = 0;

	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, chunk_start, 1);
	read_unlock(&em_tree->lock);

	BUG_ON(!em || em->start != chunk_start);
	map = (struct map_lookup *)em->bdev;

	length = em->len;
	if (map->type & BTRFS_BLOCK_GROUP_RAID10)
		do_div(length, map->num_stripes / map->sub_stripes);
	else if (map->type & BTRFS_BLOCK_GROUP_RAID0)
		do_div(length, map->num_stripes);

	buf = kzalloc(sizeof(u64) * map->num_stripes, GFP_NOFS);
	BUG_ON(!buf); /* -ENOMEM */

	for (i = 0; i < map->num_stripes; i++) {
		if (devid && map->stripes[i].dev->devid != devid)
			continue;
		if (map->stripes[i].physical > physical ||
		    map->stripes[i].physical + length <= physical)
			continue;

		stripe_nr = physical - map->stripes[i].physical;
		do_div(stripe_nr, map->stripe_len);

		if (map->type & BTRFS_BLOCK_GROUP_RAID10) {
			stripe_nr = stripe_nr * map->num_stripes + i;
			do_div(stripe_nr, map->sub_stripes);
		} else if (map->type & BTRFS_BLOCK_GROUP_RAID0) {
			stripe_nr = stripe_nr * map->num_stripes + i;
		}
		bytenr = chunk_start + stripe_nr * map->stripe_len;
		WARN_ON(nr >= map->num_stripes);
		for (j = 0; j < nr; j++) {
			if (buf[j] == bytenr)
				break;
		}
		if (j == nr) {
			WARN_ON(nr >= map->num_stripes);
			buf[nr++] = bytenr;
		}
	}

	*logical = buf;
	*naddrs = nr;
	*stripe_len = map->stripe_len;

	free_extent_map(em);
	return 0;
}