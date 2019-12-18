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
struct direntry_uarea {int entry_count; int* entry_sizes; int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int DIRENTRY_VI_FIRST_DIRENTRY_ITEM ; 

__attribute__((used)) static int direntry_check_right(struct virtual_item *vi, int free)
{
	int i;
	int entries = 0;
	struct direntry_uarea *dir_u = vi->vi_uarea;

	for (i = dir_u->entry_count - 1; i >= 0; i--) {
		if (dir_u->entry_sizes[i] > free)
			/* i-th entry doesn't fit into the remaining free space */
			break;

		free -= dir_u->entry_sizes[i];
		entries++;
	}
	BUG_ON(entries == dir_u->entry_count);

	/* "." and ".." can not be separated from each other */
	if ((dir_u->flags & DIRENTRY_VI_FIRST_DIRENTRY_ITEM)
	    && entries > dir_u->entry_count - 2)
		entries = dir_u->entry_count - 2;

	return entries ? : -1;
}