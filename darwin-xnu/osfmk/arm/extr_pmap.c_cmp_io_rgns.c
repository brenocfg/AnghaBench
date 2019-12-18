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
struct TYPE_2__ {scalar_t__ addr; scalar_t__ len; } ;
typedef  TYPE_1__ pmap_io_range_t ;

/* Variables and functions */

__attribute__((used)) static int
cmp_io_rgns(const void *a, const void *b)
{
	const pmap_io_range_t *range_a = a;
	const pmap_io_range_t *range_b = b;
	if ((range_b->addr + range_b->len) <= range_a->addr)
		return 1;
	else if ((range_a->addr + range_a->len) <= range_b->addr)
		return -1;
	else
		return 0;
}