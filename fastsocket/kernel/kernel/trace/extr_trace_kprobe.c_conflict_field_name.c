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
struct probe_arg {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * reserved_field_names ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

__attribute__((used)) static int conflict_field_name(const char *name,
			       struct probe_arg *args, int narg)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(reserved_field_names); i++)
		if (strcmp(reserved_field_names[i], name) == 0)
			return 1;
	for (i = 0; i < narg; i++)
		if (strcmp(args[i].name, name) == 0)
			return 1;
	return 0;
}