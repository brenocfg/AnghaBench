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
typedef  int /*<<< orphan*/  Elf ;
typedef  int /*<<< orphan*/  Dwarf_Ptr ;
typedef  int /*<<< orphan*/  Dwarf_Handler ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int DW_DLC_READ ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLE_DEBUG_INFO_NULL ; 
 int DW_DLE_NONE ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int _dwarf_alloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _dwarf_elf_deinit (int /*<<< orphan*/ ) ; 
 int _dwarf_elf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int _dwarf_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

int
dwarf_elf_init(Elf *elf, int mode, Dwarf_Handler errhand, Dwarf_Ptr errarg,
    Dwarf_Debug *ret_dbg, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	int ret;

	if (elf == NULL || ret_dbg == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (mode != DW_DLC_READ) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (_dwarf_alloc(&dbg, mode, error) != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	if (_dwarf_elf_init(dbg, elf, error) != DW_DLE_NONE) {
		free(dbg);
		return (DW_DLV_ERROR);
	}

	if ((ret = _dwarf_init(dbg, 0, errhand, errarg, error)) !=
	    DW_DLE_NONE) {
		_dwarf_elf_deinit(dbg);
		free(dbg);
		if (ret == DW_DLE_DEBUG_INFO_NULL)
			return (DW_DLV_NO_ENTRY);
		else
			return (DW_DLV_ERROR);
	}

	*ret_dbg = dbg;

	return (DW_DLV_OK);
}