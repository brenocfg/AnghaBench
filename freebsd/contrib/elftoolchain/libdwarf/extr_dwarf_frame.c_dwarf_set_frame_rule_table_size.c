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
struct TYPE_3__ {int /*<<< orphan*/  dbg_frame_rule_table_size; } ;
typedef  int /*<<< orphan*/  Dwarf_Half ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */

Dwarf_Half
dwarf_set_frame_rule_table_size(Dwarf_Debug dbg, Dwarf_Half value)
{
	Dwarf_Half old_value;

	old_value = dbg->dbg_frame_rule_table_size;
	dbg->dbg_frame_rule_table_size = value;

	return (old_value);
}