#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ ds_size; scalar_t__ ds_data; } ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int /*<<< orphan*/  DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 TYPE_1__* _dwarf_find_section (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 

int
dwarf_get_str(Dwarf_Debug dbg, Dwarf_Off offset, char **string,
    Dwarf_Signed *ret_strlen, Dwarf_Error *error)
{
	Dwarf_Section *ds;

	if (dbg == NULL || string == NULL || ret_strlen == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	ds = _dwarf_find_section(dbg, ".debug_str");
	if (ds == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	if (offset > ds->ds_size) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (offset == ds->ds_size) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	}

	*string = (char *) ds->ds_data + offset;
	*ret_strlen = strlen(*string);

	return (DW_DLV_OK);
}