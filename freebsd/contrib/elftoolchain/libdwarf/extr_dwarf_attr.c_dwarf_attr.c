#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * die_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  int /*<<< orphan*/ * Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/ * _dwarf_attr_find (TYPE_1__*,int /*<<< orphan*/ ) ; 

int
dwarf_attr(Dwarf_Die die, Dwarf_Half attr, Dwarf_Attribute *atp,
    Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_Attribute at;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || atp == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if ((at = _dwarf_attr_find(die, attr)) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	*atp = at;

	return (DW_DLV_OK);
}