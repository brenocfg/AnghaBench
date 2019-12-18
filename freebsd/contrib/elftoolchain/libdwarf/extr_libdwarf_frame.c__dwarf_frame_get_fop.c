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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Frame_Op ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_MEMORY ; 
 int DW_DLE_NONE ; 
 int _dwarf_frame_convert_inst (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * calloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

int
_dwarf_frame_get_fop(Dwarf_Debug dbg, uint8_t addr_size, uint8_t *insts,
    Dwarf_Unsigned len, Dwarf_Frame_Op **ret_oplist, Dwarf_Signed *ret_opcnt,
    Dwarf_Error *error)
{
	Dwarf_Frame_Op *oplist;
	Dwarf_Unsigned count;
	int ret;

	ret = _dwarf_frame_convert_inst(dbg, addr_size, insts, len, &count,
	    NULL, NULL, error);
	if (ret != DW_DLE_NONE)
		return (ret);

	if ((oplist = calloc(count, sizeof(Dwarf_Frame_Op))) == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_MEMORY);
		return (DW_DLE_MEMORY);
	}

	ret = _dwarf_frame_convert_inst(dbg, addr_size, insts, len, &count,
	    oplist, NULL, error);
	if (ret != DW_DLE_NONE) {
		free(oplist);
		return (ret);
	}

	*ret_oplist = oplist;
	*ret_opcnt = count;

	return (DW_DLE_NONE);
}