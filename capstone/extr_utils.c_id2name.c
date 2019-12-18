#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int const id; char const* name; } ;
typedef  TYPE_1__ name_map ;

/* Variables and functions */

const char *id2name(const name_map* map, int max, const unsigned int id)
{
	int i;

	for (i = 0; i < max; i++) {
		if (map[i].id == id) {
			return map[i].name;
		}
	}

	// nothing match
	return NULL;
}