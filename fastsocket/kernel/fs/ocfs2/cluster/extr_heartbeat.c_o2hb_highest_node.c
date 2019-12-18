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

/* Variables and functions */
 int find_next_bit (unsigned long*,int,int) ; 

__attribute__((used)) static int o2hb_highest_node(unsigned long *nodes,
			     int numbits)
{
	int highest, node;

	highest = numbits;
	node = -1;
	while ((node = find_next_bit(nodes, numbits, node + 1)) != -1) {
		if (node >= numbits)
			break;

		highest = node;
	}

	return highest;
}