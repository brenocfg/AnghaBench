#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int at_form; TYPE_1__* u; } ;
struct TYPE_11__ {int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_10__ {scalar_t__ u64; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  scalar_t__ Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DW_AT_abstract_origin ; 
 scalar_t__ DW_AT_specification ; 
 scalar_t__ DW_AT_type ; 
 int /*<<< orphan*/  DW_DLA_DIE ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
#define  DW_FORM_addr 138 
#define  DW_FORM_data1 137 
#define  DW_FORM_data2 136 
#define  DW_FORM_data4 135 
#define  DW_FORM_data8 134 
#define  DW_FORM_ref1 133 
#define  DW_FORM_ref2 132 
#define  DW_FORM_ref4 131 
#define  DW_FORM_ref8 130 
#define  DW_FORM_ref_udata 129 
#define  DW_FORM_udata 128 
 TYPE_3__* _dwarf_attr_find (TYPE_2__*,scalar_t__) ; 
 TYPE_2__* _dwarf_die_find (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  dwarf_dealloc (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 

int
dwarf_attrval_unsigned(Dwarf_Die die, Dwarf_Half attr, Dwarf_Unsigned *valp, Dwarf_Error *err)
{
	Dwarf_Attribute at;
	Dwarf_Die die1;
	Dwarf_Unsigned val;
	Dwarf_Debug dbg;
	int first;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || valp == NULL) {
		DWARF_SET_ERROR(dbg, err, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*valp = 0;

	die1 = NULL;
	for (;;) {
		if ((at = _dwarf_attr_find(die, attr)) != NULL ||
		    attr != DW_AT_type)
			break;
		if ((at = _dwarf_attr_find(die, DW_AT_abstract_origin)) ==
		    NULL &&
		    (at = _dwarf_attr_find(die, DW_AT_specification)) == NULL)
			break;

		switch (at->at_form) {
		case DW_FORM_ref1:
		case DW_FORM_ref2:
		case DW_FORM_ref4:
		case DW_FORM_ref8:
		case DW_FORM_ref_udata:
			val = at->u[0].u64;
			first = (die1 == NULL);
			die1 = _dwarf_die_find(die, val);
			if (!first)
				dwarf_dealloc(dbg, die, DW_DLA_DIE);
			if (die1 == NULL) {
				DWARF_SET_ERROR(dbg, err, DW_DLE_NO_ENTRY);
				return (DW_DLV_NO_ENTRY);
			}
			die = die1;
			break;
		default:
			DWARF_SET_ERROR(dbg, err, DW_DLE_ATTR_FORM_BAD);
			return (DW_DLV_ERROR);
		}
	}

	if (at == NULL) {
		DWARF_SET_ERROR(dbg, err, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	switch (at->at_form) {
	case DW_FORM_addr:
	case DW_FORM_data1:
	case DW_FORM_data2:
	case DW_FORM_data4:
	case DW_FORM_data8:
	case DW_FORM_udata:
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_ref8:
	case DW_FORM_ref_udata:
		*valp = at->u[0].u64;
		break;
	default:
		if (die1 != NULL)
			dwarf_dealloc(dbg, die1, DW_DLA_DIE);
		DWARF_SET_ERROR(dbg, err, DW_DLE_ATTR_FORM_BAD);
		return (DW_DLV_ERROR);
	}

	if (die1 != NULL)
		dwarf_dealloc(dbg, die1, DW_DLA_DIE);

	return (DW_DLV_OK);
}