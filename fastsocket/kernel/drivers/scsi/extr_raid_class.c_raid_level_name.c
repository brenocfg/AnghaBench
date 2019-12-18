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
typedef  enum raid_level { ____Placeholder_raid_level } raid_level ;
struct TYPE_3__ {int value; char* name; } ;

/* Variables and functions */
 int ARRAY_SIZE (TYPE_1__*) ; 
 TYPE_1__* raid_levels ; 

__attribute__((used)) static const char *raid_level_name(enum raid_level level)
{
	int i;
	char *name = NULL;

	for (i = 0; i < ARRAY_SIZE(raid_levels); i++) {
		if (raid_levels[i].value == level) {
			name = raid_levels[i].name;
			break;
		}
	}
	return name;
}