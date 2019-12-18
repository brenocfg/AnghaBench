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
struct raid_type {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 struct raid_type* ARRAY_END (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raid_types ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static struct raid_type *get_raid_type(char *name)
{
	struct raid_type *r = ARRAY_END(raid_types);

	while (r-- > raid_types) {
		if (!strcmp(r->name, name))
			return r;
	}

	return NULL;
}