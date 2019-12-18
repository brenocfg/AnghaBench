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
typedef  scalar_t__ Dwarf_P_Die ;

/* Variables and functions */

int
_dwarf_die_count_links(Dwarf_P_Die parent, Dwarf_P_Die child,
    Dwarf_P_Die left_sibling, Dwarf_P_Die right_sibling)
{
	int count;

	count = 0;

	if (parent)
		count++;
	if (child)
		count++;
	if (left_sibling)
		count++;
	if (right_sibling)
		count++;

	return (count);
}