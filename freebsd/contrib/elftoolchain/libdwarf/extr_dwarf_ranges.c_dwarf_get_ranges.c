#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  dbg_cu; int /*<<< orphan*/  dbg_info_loaded; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Ranges ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 int DW_DLV_ERROR ; 
 int /*<<< orphan*/  STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int _dwarf_get_ranges (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_info_load (TYPE_1__*,int,int,int /*<<< orphan*/ *) ; 

int
dwarf_get_ranges(Dwarf_Debug dbg, Dwarf_Off offset, Dwarf_Ranges **ranges,
    Dwarf_Signed *ret_cnt, Dwarf_Unsigned *ret_byte_cnt, Dwarf_Error *error)
{

	if (dbg == NULL || ranges == NULL || ret_cnt == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (!dbg->dbg_info_loaded) {
		if (_dwarf_info_load(dbg, 1, 1, error) != DW_DLE_NONE)
			return (DW_DLV_ERROR);
	}

	return (_dwarf_get_ranges(dbg, STAILQ_FIRST(&dbg->dbg_cu), offset,
	    ranges, ret_cnt, ret_byte_cnt, error));
}