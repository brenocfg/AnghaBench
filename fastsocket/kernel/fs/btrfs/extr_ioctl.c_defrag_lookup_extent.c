#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inode {int dummy; } ;
struct extent_map_tree {int /*<<< orphan*/  lock; } ;
struct extent_map {int dummy; } ;
struct extent_io_tree {int dummy; } ;
struct TYPE_2__ {struct extent_io_tree io_tree; struct extent_map_tree extent_tree; } ;

/* Variables and functions */
 TYPE_1__* BTRFS_I (struct inode*) ; 
 scalar_t__ IS_ERR (struct extent_map*) ; 
 scalar_t__ PAGE_CACHE_SIZE ; 
 struct extent_map* btrfs_get_extent (struct inode*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_extent (struct extent_io_tree*,scalar_t__,scalar_t__) ; 
 struct extent_map* lookup_extent_mapping (struct extent_map_tree*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  read_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  read_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unlock_extent (struct extent_io_tree*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static struct extent_map *defrag_lookup_extent(struct inode *inode, u64 start)
{
	struct extent_map_tree *em_tree = &BTRFS_I(inode)->extent_tree;
	struct extent_io_tree *io_tree = &BTRFS_I(inode)->io_tree;
	struct extent_map *em;
	u64 len = PAGE_CACHE_SIZE;

	/*
	 * hopefully we have this extent in the tree already, try without
	 * the full extent lock
	 */
	read_lock(&em_tree->lock);
	em = lookup_extent_mapping(em_tree, start, len);
	read_unlock(&em_tree->lock);

	if (!em) {
		/* get the big lock and read metadata off disk */
		lock_extent(io_tree, start, start + len - 1);
		em = btrfs_get_extent(inode, NULL, 0, start, len, 0);
		unlock_extent(io_tree, start, start + len - 1);

		if (IS_ERR(em))
			return NULL;
	}

	return em;
}