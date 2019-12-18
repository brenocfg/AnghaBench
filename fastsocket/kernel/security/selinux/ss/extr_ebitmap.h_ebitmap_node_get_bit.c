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
struct ebitmap_node {unsigned int* maps; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned int EBITMAP_BIT ; 
 unsigned int EBITMAP_NODE_INDEX (struct ebitmap_node*,unsigned int) ; 
 unsigned int EBITMAP_NODE_OFFSET (struct ebitmap_node*,unsigned int) ; 
 unsigned int EBITMAP_UNIT_NUMS ; 

__attribute__((used)) static inline int ebitmap_node_get_bit(struct ebitmap_node *n,
				       unsigned int bit)
{
	unsigned int index = EBITMAP_NODE_INDEX(n, bit);
	unsigned int ofs = EBITMAP_NODE_OFFSET(n, bit);

	BUG_ON(index >= EBITMAP_UNIT_NUMS);
	if ((n->maps[index] & (EBITMAP_BIT << ofs)))
		return 1;
	return 0;
}