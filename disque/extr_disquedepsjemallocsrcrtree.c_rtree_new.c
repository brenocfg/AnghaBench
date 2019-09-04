#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int height; int /*<<< orphan*/ * start_level; TYPE_1__* levels; int /*<<< orphan*/ * dalloc; int /*<<< orphan*/ * alloc; } ;
typedef  TYPE_2__ rtree_t ;
typedef  int /*<<< orphan*/  rtree_node_dalloc_t ;
typedef  int /*<<< orphan*/  rtree_node_alloc_t ;
struct TYPE_4__ {unsigned int bits; unsigned int cumbits; int /*<<< orphan*/ * subtree; } ;

/* Variables and functions */
 unsigned int RTREE_BITS_PER_LEVEL ; 
 unsigned int RTREE_HEIGHT_MAX ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  hmin (unsigned int,unsigned int) ; 

bool
rtree_new(rtree_t *rtree, unsigned bits, rtree_node_alloc_t *alloc,
    rtree_node_dalloc_t *dalloc)
{
	unsigned bits_in_leaf, height, i;

	assert(bits > 0 && bits <= (sizeof(uintptr_t) << 3));

	bits_in_leaf = (bits % RTREE_BITS_PER_LEVEL) == 0 ? RTREE_BITS_PER_LEVEL
	    : (bits % RTREE_BITS_PER_LEVEL);
	if (bits > bits_in_leaf) {
		height = 1 + (bits - bits_in_leaf) / RTREE_BITS_PER_LEVEL;
		if ((height-1) * RTREE_BITS_PER_LEVEL + bits_in_leaf != bits)
			height++;
	} else
		height = 1;
	assert((height-1) * RTREE_BITS_PER_LEVEL + bits_in_leaf == bits);

	rtree->alloc = alloc;
	rtree->dalloc = dalloc;
	rtree->height = height;

	/* Root level. */
	rtree->levels[0].subtree = NULL;
	rtree->levels[0].bits = (height > 1) ? RTREE_BITS_PER_LEVEL :
	    bits_in_leaf;
	rtree->levels[0].cumbits = rtree->levels[0].bits;
	/* Interior levels. */
	for (i = 1; i < height-1; i++) {
		rtree->levels[i].subtree = NULL;
		rtree->levels[i].bits = RTREE_BITS_PER_LEVEL;
		rtree->levels[i].cumbits = rtree->levels[i-1].cumbits +
		    RTREE_BITS_PER_LEVEL;
	}
	/* Leaf level. */
	if (height > 1) {
		rtree->levels[height-1].subtree = NULL;
		rtree->levels[height-1].bits = bits_in_leaf;
		rtree->levels[height-1].cumbits = bits;
	}

	/* Compute lookup table to be used by rtree_start_level(). */
	for (i = 0; i < RTREE_HEIGHT_MAX; i++) {
		rtree->start_level[i] = hmin(RTREE_HEIGHT_MAX - 1 - i, height -
		    1);
	}

	return (false);
}