#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct _Dwarf_P_Section {int dummy; } ;
struct TYPE_11__ {int /*<<< orphan*/  dbgp_seccnt; int /*<<< orphan*/  dbgp_seclist; } ;
struct TYPE_10__ {struct TYPE_10__* ds_name; scalar_t__ ds_cap; int /*<<< orphan*/ * ds_data; } ;
typedef  TYPE_1__* Dwarf_P_Section ;
typedef  TYPE_2__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_2__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ _SECTION_INIT_SIZE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  ds_next ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 TYPE_1__* strdup (char const*) ; 

int
_dwarf_section_init(Dwarf_P_Debug dbg, Dwarf_P_Section *dsp, const char *name,
    int pseudo, Dwarf_Error *error)
{
	Dwarf_P_Section ds;

	assert(dbg != NULL && dsp != NULL && name != NULL);

	if ((ds = calloc(1, sizeof(struct _Dwarf_P_Section))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	if ((ds->ds_name = strdup(name)) == NULL) {
		free(ds);
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	if (!pseudo) {
		ds->ds_cap = _SECTION_INIT_SIZE;
		if ((ds->ds_data = malloc((size_t) ds->ds_cap)) == NULL) {
			free(ds->ds_name);
			free(ds);
			DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
			return (DW_DLE_MEMORY);
		}
		STAILQ_INSERT_TAIL(&dbg->dbgp_seclist, ds, ds_next);
		dbg->dbgp_seccnt++;
	}

	*dsp = ds;

	return (DW_DLE_NONE);
}