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
struct exception_table_entry {unsigned long insn; unsigned long fixup; } ;

/* Variables and functions */

__attribute__((used)) static inline unsigned long search_one_table(const struct exception_table_entry *first,
					     const struct exception_table_entry *last,
					     unsigned long value)
{
        while (first <= last) {
		const struct exception_table_entry __attribute__((aligned(8))) *mid;
		long diff;

		mid = (last - first) / 2 + first;
		diff = mid->insn - value;
                if (diff == 0)
                        return mid->fixup;
                else if (diff < 0)
                        first = mid + 1;
                else
                        last = mid - 1;
        }
        return 0;
}