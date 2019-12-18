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
typedef  int /*<<< orphan*/  Dwarf_P_Die ;
typedef  int /*<<< orphan*/  Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Attribute ;

/* Variables and functions */
 int /*<<< orphan*/  DW_AT_comp_dir ; 
 scalar_t__ DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_DLV_BADADDR ; 
 scalar_t__ _dwarf_add_string_attr (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

Dwarf_P_Attribute
dwarf_add_AT_comp_dir(Dwarf_P_Die die, char *dir, Dwarf_Error *error)
{
	Dwarf_Attribute at;

	if (_dwarf_add_string_attr(die, &at, DW_AT_comp_dir, dir, error) !=
	    DW_DLE_NONE)
		return (DW_DLV_BADADDR);

	return (at);
}