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
struct TYPE_6__ {int /*<<< orphan*/ * dbg_iface; } ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Obj_Access_Interface ;
typedef  int /*<<< orphan*/  Dwarf_Handler ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLC_READ ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 scalar_t__ DW_DLE_NONE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 scalar_t__ _dwarf_alloc (TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 

int
dwarf_object_init(Dwarf_Obj_Access_Interface *iface, Dwarf_Handler errhand,
    Dwarf_Ptr errarg, Dwarf_Debug *ret_dbg, Dwarf_Error *error)
{
	Dwarf_Debug dbg;

	if (iface == NULL || ret_dbg == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (_dwarf_alloc(&dbg, DW_DLC_READ, error) != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	dbg->dbg_iface = iface;

	if (_dwarf_init(dbg, 0, errhand, errarg, error) != DW_DLE_NONE) {
		free(dbg);
		return (DW_DLV_ERROR);
	}

	*ret_dbg = dbg;

	return (DW_DLV_OK);
}