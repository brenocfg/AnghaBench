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
struct unwind_table_entry {scalar_t__ region_start; } ;

/* Variables and functions */

__attribute__((used)) static void
unwind_table_sort(struct unwind_table_entry *start,
		  struct unwind_table_entry *finish)
{
	struct unwind_table_entry el, *p, *q;

	for (p = start + 1; p < finish; ++p) {
		if (p[0].region_start < p[-1].region_start) {
			el = *p;
			q = p;
			do {
				q[0] = q[-1];
				--q;
			} while (q > start && 
				 el.region_start < q[-1].region_start);
			*q = el;
		}
	}
}