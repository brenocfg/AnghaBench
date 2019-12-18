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
struct config_group {int /*<<< orphan*/  cg_item; int /*<<< orphan*/ * cg_subsys; struct config_group** default_groups; } ;

/* Variables and functions */
 int /*<<< orphan*/  unlink_obj (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unlink_group(struct config_group *group)
{
	int i;
	struct config_group *new_group;

	if (group->default_groups) {
		for (i = 0; group->default_groups[i]; i++) {
			new_group = group->default_groups[i];
			unlink_group(new_group);
		}
	}

	group->cg_subsys = NULL;
	unlink_obj(&group->cg_item);
}