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

__attribute__((used)) static unsigned int
__lookup(struct radix_tree_node *slot, void ***results, unsigned long *indices,
	unsigned long index, unsigned int max_items, unsigned long *next_index)
{
	unsigned int nr_found = 0;
	unsigned int shift, height;
	unsigned long i;

	height = slot->height;
	if (height == 0)
		goto out;
	shift = (height-1) * RADIX_TREE_MAP_SHIFT;

	for ( ; height > 1; height--) {
		i = (index >> shift) & RADIX_TREE_MAP_MASK;
		for (;;) {
			if (slot->slots[i] != NULL)
				break;
			index &= ~((1UL << shift) - 1);
			index += 1UL << shift;
			if (index == 0)
				goto out;	/* 32-bit wraparound */
			i++;
			if (i == RADIX_TREE_MAP_SIZE)
				goto out;
		}

		shift -= RADIX_TREE_MAP_SHIFT;
		slot = rcu_dereference(slot->slots[i]);
		if (slot == NULL)
			goto out;
	}

	/* Bottom level: grab some items */
	for (i = index & RADIX_TREE_MAP_MASK; i < RADIX_TREE_MAP_SIZE; i++) {
		if (slot->slots[i]) {
			results[nr_found] = &(slot->slots[i]);
			if (indices)
				indices[nr_found] = index;
			if (++nr_found == max_items) {
				index++;
				goto out;
			}
		}
		index++;
	}
out:
	*next_index = index;
	return nr_found;
}