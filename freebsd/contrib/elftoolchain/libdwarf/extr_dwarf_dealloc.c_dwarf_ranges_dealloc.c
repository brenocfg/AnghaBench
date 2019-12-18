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
typedef  int /*<<< orphan*/  Dwarf_Ranges ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */

void
dwarf_ranges_dealloc(Dwarf_Debug dbg, Dwarf_Ranges *ranges,
    Dwarf_Signed range_count)
{
	/*
	 * In this libdwarf implementation, ranges information is
	 * kept by a STAILQ inside Dwarf_Debug object. The client
	 * does not need to free the memory returned by
	 * `dwarf_get_ranges()` or `dwarf_get_ranges_a()`.
	 */

	(void) dbg; (void) ranges; (void) range_count;
}