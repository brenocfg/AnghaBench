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
struct extent_map_tree {int dummy; } ;
struct extent_map {scalar_t__ start; scalar_t__ block_start; int /*<<< orphan*/  block_len; int /*<<< orphan*/  flags; scalar_t__ len; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  EXTENT_FLAG_COMPRESSED ; 
 scalar_t__ EXTENT_MAP_LAST_BYTE ; 
 int add_extent_mapping (struct extent_map_tree*,struct extent_map*) ; 
 scalar_t__ extent_map_end (struct extent_map*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int merge_extent_mapping(struct extent_map_tree *em_tree,
				struct extent_map *existing,
				struct extent_map *em,
				u64 map_start, u64 map_len)
{
	u64 start_diff;

	BUG_ON(map_start < em->start || map_start >= extent_map_end(em));
	start_diff = map_start - em->start;
	em->start = map_start;
	em->len = map_len;
	if (em->block_start < EXTENT_MAP_LAST_BYTE &&
	    !test_bit(EXTENT_FLAG_COMPRESSED, &em->flags)) {
		em->block_start += start_diff;
		em->block_len -= start_diff;
	}
	return add_extent_mapping(em_tree, em);
}