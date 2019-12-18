#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dbg_arange_cnt; int /*<<< orphan*/ * dbg_arange_array; } ;
typedef  scalar_t__ Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Arange ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 scalar_t__ _dwarf_arange_init (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_aranges(Dwarf_Debug dbg, Dwarf_Arange **arlist,
    Dwarf_Signed *ret_arange_cnt, Dwarf_Error *error)
{

	if (dbg == NULL || arlist == NULL || ret_arange_cnt == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (dbg->dbg_arange_cnt == 0) {
		if (_dwarf_arange_init(dbg, error) != DW_DLE_NONE)
			return (DW_DLV_ERROR);
		if (dbg->dbg_arange_cnt == 0) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
			return (DW_DLV_NO_ENTRY);
		}
	}

	assert(dbg->dbg_arange_array != NULL);

	*arlist = dbg->dbg_arange_array;
	*ret_arange_cnt = dbg->dbg_arange_cnt;

	return (DW_DLV_OK);
}