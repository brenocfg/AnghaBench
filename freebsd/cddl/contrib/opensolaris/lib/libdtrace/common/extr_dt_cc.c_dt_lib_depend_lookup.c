#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  dtld_library; } ;
typedef  TYPE_1__ dt_list_t ;
typedef  TYPE_1__ dt_lib_depend_t ;

/* Variables and functions */
 TYPE_1__* dt_list_next (TYPE_1__*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char const*) ; 

dt_lib_depend_t *
dt_lib_depend_lookup(dt_list_t *dld, const char *arg)
{
	dt_lib_depend_t *dldn;

	for (dldn = dt_list_next(dld); dldn != NULL;
	    dldn = dt_list_next(dldn)) {
		if (strcmp(dldn->dtld_library, arg) == 0)
			return (dldn);
	}

	return (NULL);
}