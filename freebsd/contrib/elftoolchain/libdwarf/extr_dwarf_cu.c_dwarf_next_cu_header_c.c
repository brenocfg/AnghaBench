#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int cu_version; int cu_pointer_size; int cu_length_size; int /*<<< orphan*/  cu_type_offset; int /*<<< orphan*/  cu_type_sig; int /*<<< orphan*/  cu_next_offset; scalar_t__ cu_abbrev_offset; int /*<<< orphan*/  cu_length; } ;
struct TYPE_9__ {TYPE_2__* dbg_tu_current; TYPE_2__* dbg_cu_current; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Sig8 ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_CU ;
typedef  scalar_t__ Dwarf_Bool ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int _dwarf_info_first_cu (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_info_first_tu (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_info_next_cu (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int _dwarf_info_next_tu (TYPE_1__*,int /*<<< orphan*/ *) ; 

int
dwarf_next_cu_header_c(Dwarf_Debug dbg, Dwarf_Bool is_info,
    Dwarf_Unsigned *cu_length, Dwarf_Half *cu_version,
    Dwarf_Off *cu_abbrev_offset, Dwarf_Half *cu_pointer_size,
    Dwarf_Half *cu_offset_size, Dwarf_Half *cu_extension_size,
    Dwarf_Sig8 *type_signature, Dwarf_Unsigned *type_offset,
    Dwarf_Unsigned *cu_next_offset, Dwarf_Error *error)
{
	Dwarf_CU cu;
	int ret;

	if (dbg == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	if (is_info) {
		if (dbg->dbg_cu_current == NULL)
			ret = _dwarf_info_first_cu(dbg, error);
		else
			ret = _dwarf_info_next_cu(dbg, error);
	} else {
		if (dbg->dbg_tu_current == NULL)
			ret = _dwarf_info_first_tu(dbg, error);
		else
			ret = _dwarf_info_next_tu(dbg, error);
	}

	if (ret == DW_DLE_NO_ENTRY) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
		return (DW_DLV_NO_ENTRY);
	} else if (ret != DW_DLE_NONE)
		return (DW_DLV_ERROR);

	if (is_info) {
		if (dbg->dbg_cu_current == NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
			return (DW_DLV_NO_ENTRY);
		}
		cu = dbg->dbg_cu_current;
	} else {
		if (dbg->dbg_tu_current == NULL) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
			return (DW_DLV_NO_ENTRY);
		}
		cu = dbg->dbg_tu_current;
	}

	if (cu_length)
		*cu_length = cu->cu_length;
	if (cu_version)
		*cu_version = cu->cu_version;
	if (cu_abbrev_offset)
		*cu_abbrev_offset = (Dwarf_Off) cu->cu_abbrev_offset;
	if (cu_pointer_size)
		*cu_pointer_size = cu->cu_pointer_size;
	if (cu_offset_size) {
		if (cu->cu_length_size == 4)
			*cu_offset_size = 4;
		else
			*cu_offset_size = 8;
	}
	if (cu_extension_size) {
		if (cu->cu_length_size == 4)
			*cu_extension_size = 0;
		else
			*cu_extension_size = 4;
	}
	if (cu_next_offset)
		*cu_next_offset	= cu->cu_next_offset;

	if (!is_info) {
		if (type_signature)
			*type_signature = cu->cu_type_sig;
		if (type_offset)
			*type_offset = cu->cu_type_offset;
	}

	return (DW_DLV_OK);
}