#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int at_form; TYPE_1__* u; } ;
struct TYPE_8__ {int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_7__ {int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Bool ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_FORM_flag 129 
#define  DW_FORM_flag_present 128 
 TYPE_3__* _dwarf_attr_find (TYPE_2__*,int /*<<< orphan*/ ) ; 

int
dwarf_attrval_flag(Dwarf_Die die, Dwarf_Half attr, Dwarf_Bool *valp, Dwarf_Error *err)
{
	Dwarf_Attribute at;
	Dwarf_Debug dbg;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || valp == NULL) {
		DWARF_SET_ERROR(dbg, err, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*valp = 0;

	if ((at = _dwarf_attr_find(die, attr)) == NULL) {
		DWARF_SET_ERROR(dbg, err, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	switch (at->at_form) {
	case DW_FORM_flag:
	case DW_FORM_flag_present:
		*valp = (Dwarf_Bool) (!!at->u[0].u64);
		break;
	default:
		DWARF_SET_ERROR(dbg, err, DW_DLE_ATTR_FORM_BAD);
		return (DW_DLV_ERROR);
	}

	return (DW_DLV_OK);
}