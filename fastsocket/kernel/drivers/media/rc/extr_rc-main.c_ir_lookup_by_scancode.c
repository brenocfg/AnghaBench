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
struct rc_map {int len; TYPE_1__* scan; } ;
struct TYPE_2__ {unsigned int scancode; } ;

/* Variables and functions */

__attribute__((used)) static unsigned int ir_lookup_by_scancode(const struct rc_map *rc_map,
					  unsigned int scancode)
{
	int start = 0;
	int end = rc_map->len - 1;
	int mid;

	while (start <= end) {
		mid = (start + end) / 2;
		if (rc_map->scan[mid].scancode < scancode)
			start = mid + 1;
		else if (rc_map->scan[mid].scancode > scancode)
			end = mid - 1;
		else
			return mid;
	}

	return -1U;
}