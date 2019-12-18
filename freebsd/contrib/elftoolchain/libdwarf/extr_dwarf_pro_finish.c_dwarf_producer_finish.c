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
struct TYPE_6__ {scalar_t__ dbg_mode; } ;
typedef  int Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ DW_DLC_WRITE ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_NOCOUNT ; 
 int /*<<< orphan*/  _dwarf_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

Dwarf_Unsigned
dwarf_producer_finish(Dwarf_P_Debug dbg, Dwarf_Error *error)
{

	if (dbg == NULL || dbg->dbg_mode != DW_DLC_WRITE) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_NOCOUNT);
	}

	_dwarf_deinit(dbg);

	free(dbg);

	return (1);
}