#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ at_form; TYPE_1__* u; TYPE_2__* at_die; } ;
struct TYPE_6__ {int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_5__ {int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  scalar_t__ Dwarf_Bool ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ DW_FORM_flag ; 
 scalar_t__ DW_FORM_flag_present ; 

int
dwarf_formflag(Dwarf_Attribute at, Dwarf_Bool *return_bool, Dwarf_Error *error)
{
	int ret;
	Dwarf_Debug dbg;

	dbg = at != NULL ? at->at_die->die_dbg : NULL;

	if (at == NULL || return_bool == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (at->at_form == DW_FORM_flag ||
	    at->at_form == DW_FORM_flag_present) {
		*return_bool = (Dwarf_Bool) (!!at->u[0].u64);
		ret = DW_DLV_OK;
	} else {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ATTR_FORM_BAD);
		ret = DW_DLV_ERROR;
	}

	return (ret);
}