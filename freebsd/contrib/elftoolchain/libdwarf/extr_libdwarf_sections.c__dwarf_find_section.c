#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {size_t dbg_seccnt; TYPE_1__* dbg_section; } ;
struct TYPE_5__ {int /*<<< orphan*/ * ds_name; } ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  size_t Dwarf_Half ;
typedef  TYPE_2__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ *,char const*) ; 

Dwarf_Section *
_dwarf_find_section(Dwarf_Debug dbg, const char *name)
{
	Dwarf_Section *ds;
	Dwarf_Half i;

	assert(dbg != NULL && name != NULL);

	for (i = 0; i < dbg->dbg_seccnt; i++) {
		ds = &dbg->dbg_section[i];
		if (ds->ds_name != NULL && !strcmp(ds->ds_name, name))
			return (ds);
	}

	return (NULL);
}