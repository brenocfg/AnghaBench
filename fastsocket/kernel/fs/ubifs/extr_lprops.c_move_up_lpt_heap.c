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
struct ubifs_lpt_heap {struct ubifs_lprops** arr; } ;
struct ubifs_lprops {int hpos; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int get_heap_comp_val (struct ubifs_lprops*,int) ; 

__attribute__((used)) static void move_up_lpt_heap(struct ubifs_info *c, struct ubifs_lpt_heap *heap,
			     struct ubifs_lprops *lprops, int cat)
{
	int val1, val2, hpos;

	hpos = lprops->hpos;
	if (!hpos)
		return; /* Already top of the heap */
	val1 = get_heap_comp_val(lprops, cat);
	/* Compare to parent and, if greater, move up the heap */
	do {
		int ppos = (hpos - 1) / 2;

		val2 = get_heap_comp_val(heap->arr[ppos], cat);
		if (val2 >= val1)
			return;
		/* Greater than parent so move up */
		heap->arr[ppos]->hpos = hpos;
		heap->arr[hpos] = heap->arr[ppos];
		heap->arr[ppos] = lprops;
		lprops->hpos = ppos;
		hpos = ppos;
	} while (hpos);
}