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
typedef  int u64 ;
struct inode {int dummy; } ;
struct extent_map {scalar_t__ block_start; int len; } ;

/* Variables and functions */
 scalar_t__ EXTENT_MAP_LAST_BYTE ; 
 int defrag_check_next_extent (struct inode*,struct extent_map*) ; 
 struct extent_map* defrag_lookup_extent (struct inode*,int) ; 
 int extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  free_extent_map (struct extent_map*) ; 

__attribute__((used)) static int should_defrag_range(struct inode *inode, u64 start, int thresh,
			       u64 *last_len, u64 *skip, u64 *defrag_end)
{
	struct extent_map *em;
	int ret = 1;
	bool next_mergeable = true;

	/*
	 * make sure that once we start defragging an extent, we keep on
	 * defragging it
	 */
	if (start < *defrag_end)
		return 1;

	*skip = 0;

	em = defrag_lookup_extent(inode, start);
	if (!em)
		return 0;

	/* this will cover holes, and inline extents */
	if (em->block_start >= EXTENT_MAP_LAST_BYTE) {
		ret = 0;
		goto out;
	}

	next_mergeable = defrag_check_next_extent(inode, em);

	/*
	 * we hit a real extent, if it is big or the next extent is not a
	 * real extent, don't bother defragging it
	 */
	if ((*last_len == 0 || *last_len >= thresh) &&
	    (em->len >= thresh || !next_mergeable))
		ret = 0;
out:
	/*
	 * last_len ends up being a counter of how many bytes we've defragged.
	 * every time we choose not to defrag an extent, we reset *last_len
	 * so that the next tiny extent will force a defrag.
	 *
	 * The end result of this is that tiny extents before a single big
	 * extent will force at least part of that big extent to be defragged.
	 */
	if (ret) {
		*defrag_end = extent_map_end(em);
	} else {
		*last_len = 0;
		*skip = extent_map_end(em);
		*defrag_end = 0;
	}

	free_extent_map(em);
	return ret;
}