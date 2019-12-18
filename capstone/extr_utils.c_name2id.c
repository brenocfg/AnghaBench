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
struct TYPE_3__ {int id; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ name_map ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char const*) ; 

int name2id(const name_map* map, int max, const char *name)
{
	int i;

	for (i = 0; i < max; i++) {
		if (!strcmp(map[i].name, name)) {
			return map[i].id;
		}
	}

	// nothing match
	return -1;
}