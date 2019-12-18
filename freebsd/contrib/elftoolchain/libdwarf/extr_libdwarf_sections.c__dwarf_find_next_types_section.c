#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ds_name; } ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 TYPE_1__* _dwarf_find_section (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char*) ; 

Dwarf_Section *
_dwarf_find_next_types_section(Dwarf_Debug dbg, Dwarf_Section *ds)
{

	assert(dbg != NULL);

	if (ds == NULL)
		return (_dwarf_find_section(dbg, ".debug_types"));

	assert(ds->ds_name != NULL);

	do {
		ds++;
		if (ds->ds_name != NULL &&
		    !strcmp(ds->ds_name, ".debug_types"))
			return (ds);
	} while (ds->ds_name != NULL);

	return (NULL);
}