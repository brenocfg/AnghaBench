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
struct TYPE_3__ {int ds_ndx; int /*<<< orphan*/  ds_symndx; scalar_t__ ds_size; int /*<<< orphan*/  ds_name; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Section ;
typedef  int /*<<< orphan*/  Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_ELF_SECT_ERR ; 
 int DW_DLE_NONE ; 
 int _dwarf_pro_callback (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
_dwarf_section_callback(Dwarf_P_Debug dbg, Dwarf_P_Section ds,
    Dwarf_Unsigned type, Dwarf_Unsigned flags, Dwarf_Unsigned link,
    Dwarf_Unsigned info, Dwarf_Error *error)
{
	int ret, ndx;

	ndx = _dwarf_pro_callback(dbg, ds->ds_name, (int) ds->ds_size,
	    type, flags, link, info, &ds->ds_symndx, NULL);
	if (ndx < 0) {
		ret = DW_DLE_ELF_SECT_ERR;
		DWARF_SET_ERROR(dbg, error, ret);
		return (ret);
	}
	ds->ds_ndx = ndx;

	return (DW_DLE_NONE);
}