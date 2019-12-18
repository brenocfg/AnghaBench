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
struct ubifs_lpt_heap {int cnt; struct ubifs_lprops** arr; } ;
struct ubifs_lprops {int hpos; } ;
struct ubifs_info {int dummy; } ;

/* Variables and functions */
 int get_heap_comp_val (struct ubifs_lprops*,int) ; 

__attribute__((used)) static void adjust_lpt_heap(struct ubifs_info *c, struct ubifs_lpt_heap *heap,
			    struct ubifs_lprops *lprops, int hpos, int cat)
{
	int val1, val2, val3, cpos;

	val1 = get_heap_comp_val(lprops, cat);
	/* Compare to parent and, if greater than parent, move up the heap */
	if (hpos) {
		int ppos = (hpos - 1) / 2;

		val2 = get_heap_comp_val(heap->arr[ppos], cat);
		if (val1 > val2) {
			/* Greater than parent so move up */
			while (1) {
				heap->arr[ppos]->hpos = hpos;
				heap->arr[hpos] = heap->arr[ppos];
				heap->arr[ppos] = lprops;
				lprops->hpos = ppos;
				hpos = ppos;
				if (!hpos)
					return;
				ppos = (hpos - 1) / 2;
				val2 = get_heap_comp_val(heap->arr[ppos], cat);
				if (val1 <= val2)
					return;
				/* Still greater than parent so keep going */
			}
		}
	}

	/* Not greater than parent, so compare to children */
	while (1) {
		/* Compare to left child */
		cpos = hpos * 2 + 1;
		if (cpos >= heap->cnt)
			return;
		val2 = get_heap_comp_val(heap->arr[cpos], cat);
		if (val1 < val2) {
			/* Less than left child, so promote biggest child */
			if (cpos + 1 < heap->cnt) {
				val3 = get_heap_comp_val(heap->arr[cpos + 1],
							 cat);
				if (val3 > val2)
					cpos += 1; /* Right child is bigger */
			}
			heap->arr[cpos]->hpos = hpos;
			heap->arr[hpos] = heap->arr[cpos];
			heap->arr[cpos] = lprops;
			lprops->hpos = cpos;
			hpos = cpos;
			continue;
		}
		/* Compare to right child */
		cpos += 1;
		if (cpos >= heap->cnt)
			return;
		val3 = get_heap_comp_val(heap->arr[cpos], cat);
		if (val1 < val3) {
			/* Less than right child, so promote right child */
			heap->arr[cpos]->hpos = hpos;
			heap->arr[hpos] = heap->arr[cpos];
			heap->arr[cpos] = lprops;
			lprops->hpos = cpos;
			hpos = cpos;
			continue;
		}
		return;
	}
}