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
typedef  int /*<<< orphan*/  Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Fde ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  int /*<<< orphan*/  Dwarf_Cie ;

/* Variables and functions */

void
dwarf_fde_cie_list_dealloc(Dwarf_Debug dbg, Dwarf_Cie *cie_list,
    Dwarf_Signed cie_count, Dwarf_Fde *fde_list, Dwarf_Signed fde_count)
{
	/*
	 * In this implementation, FDE and CIE information is managed
	 * as part of the Dwarf_Debug object.  The client does not need
	 * to explicitly free these memory arenas.
	 */
	(void) dbg;
	(void) cie_list;
	(void) cie_count;
	(void) fde_list;
	(void) fde_count;
}