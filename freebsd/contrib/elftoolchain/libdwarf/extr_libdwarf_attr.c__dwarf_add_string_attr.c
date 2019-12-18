#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* u; int /*<<< orphan*/  at_form; int /*<<< orphan*/  at_attrib; TYPE_2__* at_die; } ;
struct TYPE_12__ {int /*<<< orphan*/  die_attr; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_11__ {scalar_t__ u64; scalar_t__ s; } ;
typedef  TYPE_2__* Dwarf_P_Die ;
typedef  TYPE_3__* Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_FORM_strp ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int _dwarf_attr_alloc (TYPE_2__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 int _dwarf_strtab_add (int /*<<< orphan*/ *,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_strtab_get_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at_next ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 

int
_dwarf_add_string_attr(Dwarf_P_Die die, Dwarf_P_Attribute *atp, Dwarf_Half attr,
    char *string, Dwarf_Error *error)
{
	Dwarf_Attribute at;
	Dwarf_Debug dbg;
	int ret;

	dbg = die != NULL ? die->die_dbg : NULL;

	assert(atp != NULL);

	if (die == NULL || string == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLE_ARGUMENT);
	}

	if ((ret = _dwarf_attr_alloc(die, &at, error)) != DW_DLE_NONE)
		return (ret);

	at->at_die = die;
	at->at_attrib = attr;
	at->at_form = DW_FORM_strp;
	if ((ret = _dwarf_strtab_add(dbg, string, &at->u[0].u64,
	    error)) != DW_DLE_NONE) {
		free(at);
		return (ret);
	}
	at->u[1].s = _dwarf_strtab_get_table(dbg) + at->u[0].u64;

	*atp = at;

	STAILQ_INSERT_TAIL(&die->die_attr, at, at_next);

	return (DW_DLE_NONE);
}