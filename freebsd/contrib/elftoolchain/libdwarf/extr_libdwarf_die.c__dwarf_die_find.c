#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int /*<<< orphan*/  cu_next_offset; int /*<<< orphan*/  cu_dwarf_size; scalar_t__ cu_is_info; } ;
struct TYPE_10__ {int /*<<< orphan*/ * dbg_types_sec; int /*<<< orphan*/ * dbg_info_sec; } ;
struct TYPE_9__ {TYPE_2__* die_dbg; TYPE_3__* die_cu; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  int /*<<< orphan*/  Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Die ;
typedef  TYPE_2__* Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_CU ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int _dwarf_die_parse (TYPE_2__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

Dwarf_Die
_dwarf_die_find(Dwarf_Die die, Dwarf_Unsigned off)
{
	Dwarf_Debug dbg;
	Dwarf_Section *ds;
	Dwarf_CU cu;
	Dwarf_Die die1;
	Dwarf_Error de;
	int ret;

	cu = die->die_cu;
	dbg = die->die_dbg;
	ds = cu->cu_is_info ? dbg->dbg_info_sec : dbg->dbg_types_sec;

	ret = _dwarf_die_parse(dbg, ds, cu, cu->cu_dwarf_size, off,
	    cu->cu_next_offset, &die1, 0, &de);

	if (ret == DW_DLE_NONE)
		return (die1);
	else
		return (NULL);
}