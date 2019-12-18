#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  cu_next_offset; int /*<<< orphan*/  cu_dwarf_size; scalar_t__ cu_is_info; } ;
struct TYPE_13__ {int /*<<< orphan*/ * dbg_types_sec; int /*<<< orphan*/ * dbg_info_sec; } ;
struct TYPE_12__ {int /*<<< orphan*/  die_next_off; TYPE_3__* die_dbg; TYPE_4__* die_cu; TYPE_1__* die_ab; } ;
struct TYPE_11__ {scalar_t__ ab_children; } ;
typedef  int /*<<< orphan*/  Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  TYPE_3__* Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_CU ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ DW_CHILDREN_no ; 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int _dwarf_die_parse (TYPE_3__*,int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dwarf_child(Dwarf_Die die, Dwarf_Die *ret_die, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_Section *ds;
	Dwarf_CU cu;
	int ret;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || ret_die == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (die->die_ab->ab_children == DW_CHILDREN_no)
		return (DW_DLV_NO_ENTRY);

	dbg = die->die_dbg;
	cu = die->die_cu;
	ds = cu->cu_is_info ? dbg->dbg_info_sec : dbg->dbg_types_sec;
	ret = _dwarf_die_parse(die->die_dbg, ds, cu, cu->cu_dwarf_size,
	    die->die_next_off, cu->cu_next_offset, ret_die, 0, error);

	if (ret == DW_DLE_NO_ENTRY) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	} else if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	return (DW_DLV_OK);
}