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
struct map_groups {int /*<<< orphan*/ * removed_maps; int /*<<< orphan*/ * maps; } ;

/* Variables and functions */
 int MAP__NR_TYPES ; 
 int /*<<< orphan*/  maps__delete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  maps__delete_removed (int /*<<< orphan*/ *) ; 

void map_groups__exit(struct map_groups *mg)
{
	int i;

	for (i = 0; i < MAP__NR_TYPES; ++i) {
		maps__delete(&mg->maps[i]);
		maps__delete_removed(&mg->removed_maps[i]);
	}
}