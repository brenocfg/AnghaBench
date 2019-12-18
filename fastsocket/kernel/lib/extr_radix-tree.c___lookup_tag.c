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
struct radix_tree_node {unsigned int height; void** slots; } ;

/* Variables and functions */
 unsigned long RADIX_TREE_MAP_MASK ; 
 unsigned int RADIX_TREE_MAP_SHIFT ; 
 unsigned long RADIX_TREE_MAP_SIZE ; 
 struct radix_tree_node* rcu_dereference (void*) ; 
 scalar_t__ tag_get (struct radix_tree_node*,unsigned int,unsigned long) ; 

__attribute__((used)) static unsigned int
__lookup_tag(struct radix_tree_node *slot, void ***results, unsigned long index,
	unsigned int max_items, unsigned long *next_index, unsigned int tag)
{
	unsigned int nr_found = 0;
	unsigned int shift, height;

	height = slot->height;
	if (height == 0)
		goto out;
	shift = (height-1) * RADIX_TREE_MAP_SHIFT;

	while (height > 0) {
		unsigned long i = (index >> shift) & RADIX_TREE_MAP_MASK ;

		for (;;) {
			if (tag_get(slot, tag, i))
				break;
			index &= ~((1UL << shift) - 1);
			index += 1UL << shift;
			if (index == 0)
				goto out;	/* 32-bit wraparound */
			i++;
			if (i == RADIX_TREE_MAP_SIZE)
				goto out;
		}
		height--;
		if (height == 0) {	/* Bottom level: grab some items */
			unsigned long j = index & RADIX_TREE_MAP_MASK;

			for ( ; j < RADIX_TREE_MAP_SIZE; j++) {
				index++;
				if (!tag_get(slot, tag, j))
					continue;
				/*
				 * Even though the tag was found set, we need to
				 * recheck that we have a non-NULL node, because
				 * if this lookup is lockless, it may have been
				 * subsequently deleted.
				 *
				 * Similar care must be taken in any place that
				 * lookup ->slots[x] without a lock (ie. can't
				 * rely on its value remaining the same).
				 */
				if (slot->slots[j]) {
					results[nr_found++] = &(slot->slots[j]);
					if (nr_found == max_items)
						goto out;
				}
			}
		}
		shift -= RADIX_TREE_MAP_SHIFT;
		slot = rcu_dereference(slot->slots[i]);
		if (slot == NULL)
			break;
	}
out:
	*next_index = index;
	return nr_found;
}