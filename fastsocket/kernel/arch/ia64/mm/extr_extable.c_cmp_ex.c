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
typedef  scalar_t__ u64 ;
struct exception_table_entry {scalar_t__ addr; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_ex(const void *a, const void *b)
{
	const struct exception_table_entry *l = a, *r = b;
	u64 lip = (u64) &l->addr + l->addr;
	u64 rip = (u64) &r->addr + r->addr;

	/* avoid overflow */
	if (lip > rip)
		return 1;
	if (lip < rip)
		return -1;
	return 0;
}