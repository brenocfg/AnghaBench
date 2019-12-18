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
struct virtual_item {struct direntry_uarea* vi_uarea; } ;
struct direntry_uarea {int entry_count; scalar_t__* entry_sizes; } ;

/* Variables and functions */

__attribute__((used)) static int direntry_part_size(struct virtual_item *vi, int first, int count)
{
	int i, retval;
	int from, to;
	struct direntry_uarea *dir_u = vi->vi_uarea;

	retval = 0;
	if (first == 0)
		from = 0;
	else
		from = dir_u->entry_count - count;
	to = from + count - 1;

	for (i = from; i <= to; i++)
		retval += dir_u->entry_sizes[i];

	return retval;
}