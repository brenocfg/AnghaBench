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
typedef  int /*<<< orphan*/  Dwarf_P_Fde ;
typedef  int /*<<< orphan*/  Dwarf_P_Die ;
typedef  int /*<<< orphan*/  Dwarf_P_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  dwarf_add_frame_fde_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Dwarf_Unsigned
dwarf_add_frame_fde(Dwarf_P_Debug dbg, Dwarf_P_Fde fde, Dwarf_P_Die die,
    Dwarf_Unsigned cie, Dwarf_Addr virt_addr, Dwarf_Unsigned code_len,
    Dwarf_Unsigned symbol_index, Dwarf_Error *error)
{

	return (dwarf_add_frame_fde_b(dbg, fde, die, cie, virt_addr, code_len,
	    symbol_index, 0, 0, error));
}