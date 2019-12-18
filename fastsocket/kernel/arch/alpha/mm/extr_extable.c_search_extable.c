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
struct exception_table_entry {int dummy; } ;

/* Variables and functions */
 unsigned long ex_to_addr (struct exception_table_entry const*) ; 

const struct exception_table_entry *
search_extable(const struct exception_table_entry *first,
	       const struct exception_table_entry *last,
	       unsigned long value)
{
        while (first <= last) {
		const struct exception_table_entry *mid;
		unsigned long mid_value;

		mid = (last - first) / 2 + first;
		mid_value = ex_to_addr(mid);
                if (mid_value == value)
                        return mid;
                else if (mid_value < value)
                        first = mid+1;
                else
                        last = mid-1;
        }

        return NULL;
}