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
typedef  int /*<<< orphan*/  Dwarf_Line ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */

void
dwarf_srclines_dealloc(Dwarf_Debug dbg, Dwarf_Line *linebuf,
	Dwarf_Signed count)
{
	/*
	 * In this libdwarf implementation, line information remains
	 * associated with the DIE for a compilation unit for the
	 * lifetime of the DIE.  The client does not need to free
	 * the memory returned by `dwarf_srclines()`.
	 */ 

	(void) dbg; (void) linebuf; (void) count;
}