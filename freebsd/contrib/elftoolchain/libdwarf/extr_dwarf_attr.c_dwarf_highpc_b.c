#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  enum Dwarf_Form_Class { ____Placeholder_Dwarf_Form_Class } Dwarf_Form_Class ;
struct TYPE_11__ {int /*<<< orphan*/  at_form; TYPE_1__* u; } ;
struct TYPE_10__ {int cu_length_size; int /*<<< orphan*/  cu_version; } ;
struct TYPE_9__ {TYPE_3__* die_cu; int /*<<< orphan*/ * die_dbg; } ;
struct TYPE_8__ {int /*<<< orphan*/  u64; } ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_CU ;
typedef  TYPE_4__* Dwarf_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_AT_high_pc ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 TYPE_4__* _dwarf_attr_find (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int dwarf_get_form_class (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int
dwarf_highpc_b(Dwarf_Die die, Dwarf_Addr *ret_highpc, Dwarf_Half *ret_form,
    enum Dwarf_Form_Class *ret_class, Dwarf_Error *error)
{
	Dwarf_Attribute at;
	Dwarf_Debug dbg;
	Dwarf_CU cu;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || ret_highpc == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if ((at = _dwarf_attr_find(die, DW_AT_high_pc)) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	*ret_highpc = at->u[0].u64;

	if (ret_form != NULL) {
		*ret_form = at->at_form;
	}

	if (ret_class != NULL) {
		cu = die->die_cu;
		*ret_class = dwarf_get_form_class(cu->cu_version,
		    DW_AT_high_pc, cu->cu_length_size == 4 ? 4 : 8,
		    at->at_form);
	}

	return (DW_DLV_OK);
}