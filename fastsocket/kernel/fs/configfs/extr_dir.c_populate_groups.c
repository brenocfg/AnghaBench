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
struct config_group {struct config_group** default_groups; } ;

/* Variables and functions */
 int create_default_group (struct config_group*,struct config_group*) ; 
 int /*<<< orphan*/  detach_groups (struct config_group*) ; 

__attribute__((used)) static int populate_groups(struct config_group *group)
{
	struct config_group *new_group;
	int ret = 0;
	int i;

	if (group->default_groups) {
		for (i = 0; group->default_groups[i]; i++) {
			new_group = group->default_groups[i];

			ret = create_default_group(group, new_group);
			if (ret) {
				detach_groups(group);
				break;
			}
		}
	}

	return ret;
}