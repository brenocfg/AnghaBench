#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int at_form; TYPE_3__* at_die; TYPE_1__* u; } ;
struct TYPE_8__ {TYPE_2__* die_cu; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_7__ {scalar_t__ cu_offset; } ;
struct TYPE_6__ {int /*<<< orphan*/  u64; } ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
#define  DW_FORM_ref1 134 
#define  DW_FORM_ref2 133 
#define  DW_FORM_ref4 132 
#define  DW_FORM_ref8 131 
#define  DW_FORM_ref_addr 130 
#define  DW_FORM_ref_udata 129 
#define  DW_FORM_sec_offset 128 

int
dwarf_global_formref(Dwarf_Attribute at, Dwarf_Off *return_offset,
    Dwarf_Error *error)
{
	int ret;
	Dwarf_Debug dbg;

	dbg = at != NULL ? at->at_die->die_dbg : NULL;

	if (at == NULL || return_offset == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	switch (at->at_form) {
	case DW_FORM_ref_addr:
	case DW_FORM_sec_offset:
		*return_offset = (Dwarf_Off) at->u[0].u64;
		ret = DW_DLV_OK;
		break;
	case DW_FORM_ref1:
	case DW_FORM_ref2:
	case DW_FORM_ref4:
	case DW_FORM_ref8:
	case DW_FORM_ref_udata:
		*return_offset = (Dwarf_Off) at->u[0].u64 +
			at->at_die->die_cu->cu_offset;
		ret = DW_DLV_OK;
		break;
	default:
		DWARF_SET_ERROR(dbg, error, DW_DLE_ATTR_FORM_BAD);
		ret = DW_DLV_ERROR;
	}

	return (ret);
}