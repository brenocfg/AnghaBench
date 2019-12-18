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
 scalar_t__ ex_to_addr (struct exception_table_entry const*) ; 

__attribute__((used)) static int cmp_ex(const void *a, const void *b)
{
	const struct exception_table_entry *x = a, *y = b;

	/* avoid overflow */
	if (ex_to_addr(x) > ex_to_addr(y))
		return 1;
	if (ex_to_addr(x) < ex_to_addr(y))
		return -1;
	return 0;
}