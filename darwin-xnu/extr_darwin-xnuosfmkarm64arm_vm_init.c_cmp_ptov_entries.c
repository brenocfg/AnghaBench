#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ len; } ;
typedef  TYPE_1__ ptov_table_entry ;

/* Variables and functions */

__attribute__((used)) static int
cmp_ptov_entries(const void *a, const void *b)
{
	const ptov_table_entry *entry_a = a;
	const ptov_table_entry *entry_b = b;
	// Sort in descending order of segment length
	if (entry_a->len < entry_b->len)
		return 1;
	else if (entry_a->len > entry_b->len)
		return -1;
	else
		return 0;
}