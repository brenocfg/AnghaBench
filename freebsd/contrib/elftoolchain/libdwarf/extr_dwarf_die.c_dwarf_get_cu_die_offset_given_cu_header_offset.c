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
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;

/* Variables and functions */
 int dwarf_get_cu_die_offset_given_cu_header_offset_b (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int
dwarf_get_cu_die_offset_given_cu_header_offset(Dwarf_Debug dbg,
    Dwarf_Off in_cu_header_offset, Dwarf_Off *out_cu_die_offset,
    Dwarf_Error *error)
{

	return (dwarf_get_cu_die_offset_given_cu_header_offset_b(dbg,
	    in_cu_header_offset, 1, out_cu_die_offset, error));
}