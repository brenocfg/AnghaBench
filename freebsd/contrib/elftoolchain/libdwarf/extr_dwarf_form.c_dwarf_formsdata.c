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
typedef  int /*<<< orphan*/  int8_t ;
typedef  int /*<<< orphan*/  int32_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_7__ {int at_form; TYPE_2__* u; TYPE_1__* at_die; } ;
struct TYPE_6__ {int /*<<< orphan*/  s64; } ;
struct TYPE_5__ {int /*<<< orphan*/ * die_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_ATTR_FORM_BAD ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
#define  DW_FORM_data1 132 
#define  DW_FORM_data2 131 
#define  DW_FORM_data4 130 
#define  DW_FORM_data8 129 
#define  DW_FORM_sdata 128 

int
dwarf_formsdata(Dwarf_Attribute at, Dwarf_Signed *return_svalue,
    Dwarf_Error *error)
{
	int ret;
	Dwarf_Debug dbg;

	dbg = at != NULL ? at->at_die->die_dbg : NULL;

	if (at == NULL || return_svalue == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	switch (at->at_form) {
	case DW_FORM_data1:
		*return_svalue = (int8_t) at->u[0].s64;
		ret = DW_DLV_OK;
		break;
	case DW_FORM_data2:
		*return_svalue = (int16_t) at->u[0].s64;
		ret = DW_DLV_OK;
		break;
	case DW_FORM_data4:
		*return_svalue = (int32_t) at->u[0].s64;
		ret = DW_DLV_OK;
		break;
	case DW_FORM_data8:
	case DW_FORM_sdata:
		*return_svalue = at->u[0].s64;
		ret = DW_DLV_OK;
		break;
	default:
		DWARF_SET_ERROR(dbg, error, DW_DLE_ATTR_FORM_BAD);
		ret = DW_DLV_ERROR;
	}

	return (ret);
}