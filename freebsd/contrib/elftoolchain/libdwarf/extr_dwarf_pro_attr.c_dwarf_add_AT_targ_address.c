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
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_P_Die ;
typedef  int /*<<< orphan*/  Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_P_Attribute ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  int /*<<< orphan*/  Dwarf_Error ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_add_AT_targ_address_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Dwarf_P_Attribute
dwarf_add_AT_targ_address(Dwarf_P_Debug dbg, Dwarf_P_Die die, Dwarf_Half attr,
    Dwarf_Unsigned pc_value, Dwarf_Signed sym_index, Dwarf_Error *error)
{

	return (dwarf_add_AT_targ_address_b(dbg, die, attr, pc_value, sym_index,
	    error));
}