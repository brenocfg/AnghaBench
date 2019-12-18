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
typedef  unsigned long u64 ;
struct exception_table_entry {int /*<<< orphan*/  addr; } ;

/* Variables and functions */

const struct exception_table_entry *
search_extable (const struct exception_table_entry *first,
		const struct exception_table_entry *last,
		unsigned long ip)
{
	const struct exception_table_entry *mid;
	unsigned long mid_ip;
	long diff;

        while (first <= last) {
		mid = &first[(last - first)/2];
		mid_ip = (u64) &mid->addr + mid->addr;
		diff = mid_ip - ip;
                if (diff == 0)
                        return mid;
                else if (diff < 0)
                        first = mid + 1;
                else
                        last = mid - 1;
        }
        return NULL;
}