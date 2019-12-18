#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct map_lookup {int num_stripes; TYPE_3__* stripes; } ;
struct extent_map {scalar_t__ bdev; } ;
struct btrfs_root {TYPE_1__* fs_info; } ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
struct btrfs_mapping_tree {TYPE_4__ map_tree; } ;
struct TYPE_7__ {TYPE_2__* dev; } ;
struct TYPE_6__ {int /*<<< orphan*/  writeable; } ;
struct TYPE_5__ {struct btrfs_mapping_tree mapping_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEGRADED ; 
 scalar_t__ btrfs_test_opt (struct btrfs_root*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 struct extent_map* lookup_extent_mapping (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 

int btrfs_chunk_readonly(struct btrfs_root *root, u64 chunk_offset)
{
	struct extent_map *em;
	struct map_lookup *map;
	struct btrfs_mapping_tree *map_tree = &root->fs_info->mapping_tree;
	int readonly = 0;
	int i;

	read_lock(&map_tree->map_tree.lock);
	em = lookup_extent_mapping(&map_tree->map_tree, chunk_offset, 1);
	read_unlock(&map_tree->map_tree.lock);
	if (!em)
		return 1;

	if (btrfs_test_opt(root, DEGRADED)) {
		free_extent_map(em);
		return 0;
	}

	map = (struct map_lookup *)em->bdev;
	for (i = 0; i < map->num_stripes; i++) {
		if (!map->stripes[i].dev->writeable) {
			readonly = 1;
			break;
		}
	}
	free_extent_map(em);
	return readonly;
}