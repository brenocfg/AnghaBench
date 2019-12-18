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
typedef  size_t Index ;

/* Variables and functions */
 size_t lengthof (char const**) ; 
 scalar_t__ pg_strcasecmp (char const*,char*) ; 

__attribute__((used)) static bool
IsSettingSafeToPropagate(char *name)
{
	/* if this list grows considerably we should switch to bsearch */
	const char *skipSettings[] = {
		"citus.propagate_set_commands",
		"client_encoding",
		"exit_on_error",
		"max_stack_depth"
	};
	Index settingIndex = 0;

	for (settingIndex = 0; settingIndex < lengthof(skipSettings); settingIndex++)
	{
		if (pg_strcasecmp(skipSettings[settingIndex], name) == 0)
		{
			return false;
		}
	}

	return true;
}