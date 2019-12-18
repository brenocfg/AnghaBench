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
struct exception_table_entry {unsigned long insn; } ;

/* Variables and functions */

const struct exception_table_entry *
search_extable(const struct exception_table_entry *first,
	       const struct exception_table_entry *last,
	       unsigned long value)
{
	while (first <= last) {
		const struct exception_table_entry *mid;

		mid = ((last - first) >> 1) + first;
		/*
		 * careful, the distance between value and insn
		 * can be larger than MAX_LONG:
		 */
		if (mid->insn < value)
			first = mid + 1;
		else if (mid->insn > value)
			last = mid - 1;
		else
			return mid;
        }
        return NULL;
}