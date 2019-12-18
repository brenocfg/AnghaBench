#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct extent_map {int /*<<< orphan*/  bdev; } ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;
struct btrfs_mapping_tree {TYPE_1__ map_tree; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 struct extent_map* lookup_extent_mapping (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_extent_mapping (TYPE_1__*,struct extent_map*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

void btrfs_mapping_tree_free(struct btrfs_mapping_tree *tree)
{
	struct extent_map *em;

	while (1) {
		write_lock(&tree->map_tree.lock);
		em = lookup_extent_mapping(&tree->map_tree, 0, (u64)-1);
		if (em)
			remove_extent_mapping(&tree->map_tree, em);
		write_unlock(&tree->map_tree.lock);
		if (!em)
			break;
		kfree(em->bdev);
		/* once for us */
		free_extent_map(em);
		/* once for the tree */
		free_extent_map(em);
	}
}