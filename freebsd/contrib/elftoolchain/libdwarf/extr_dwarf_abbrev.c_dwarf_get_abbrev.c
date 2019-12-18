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
struct TYPE_4__ {int /*<<< orphan*/  ab_atnum; int /*<<< orphan*/  ab_length; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_1__* Dwarf_Abbrev ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_ARGUMENT ; 
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_NO_ENTRY ; 
 int DW_DLV_OK ; 
 int _dwarf_abbrev_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__**,int /*<<< orphan*/ *) ; 

int
dwarf_get_abbrev(Dwarf_Debug dbg, Dwarf_Unsigned offset,
    Dwarf_Abbrev *return_abbrev, Dwarf_Unsigned *length,
    Dwarf_Unsigned *attr_count, Dwarf_Error *error)
{
	Dwarf_Abbrev ab;
	int ret;

	if (dbg == NULL || return_abbrev == NULL || length == NULL ||
	    attr_count == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	ret = _dwarf_abbrev_parse(dbg, NULL, &offset, &ab, error);
	if (ret != DW_DLE_NONE) {
		if (ret == DW_DLE_NO_ENTRY) {
			DWARF_SET_ERROR(dbg, error, DW_DLE_NO_ENTRY);
			return (DW_DLV_NO_ENTRY);
		} else
			return (DW_DLV_ERROR);
	}

	*return_abbrev = ab;
	*length = ab->ab_length;
	*attr_count = ab->ab_atnum;

	return (DW_DLV_OK);
}