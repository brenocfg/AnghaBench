#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Small ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/ * Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Locdesc ;
typedef  int Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int _dwarf_loc_fill_locexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
dwarf_loclist_from_expr_b(Dwarf_Debug dbg, Dwarf_Ptr bytes_in,
    Dwarf_Unsigned bytes_len, Dwarf_Half addr_size, Dwarf_Half offset_size,
    Dwarf_Small version, Dwarf_Locdesc **llbuf, Dwarf_Signed *listlen,
    Dwarf_Error *error)
{
	Dwarf_Locdesc *ld;
	int ret;

	if (dbg == NULL || bytes_in == NULL || bytes_len == 0 ||
	    llbuf == NULL || listlen == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (addr_size != 4 && addr_size != 8) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (offset_size != 4 && offset_size != 8) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	ret = _dwarf_loc_fill_locexpr(dbg, &ld, bytes_in, bytes_len, addr_size,
	    offset_size, version, error);
	if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	*llbuf = ld;
	*listlen = 1;

	return (DW_DLV_OK);
}