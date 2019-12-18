#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_1__* u; int /*<<< orphan*/ * at_ld; } ;
struct TYPE_9__ {int cu_length_size; int /*<<< orphan*/  cu_version; int /*<<< orphan*/  cu_pointer_size; int /*<<< orphan*/ * cu_dbg; } ;
struct TYPE_8__ {TYPE_3__* die_cu; } ;
struct TYPE_7__ {int /*<<< orphan*/  u64; int /*<<< orphan*/ * u8p; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_3__* Dwarf_CU ;
typedef  TYPE_4__* Dwarf_Attribute ;

/* Variables and functions */
 int _dwarf_loc_fill_locexpr (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

int
_dwarf_loc_add(Dwarf_Die die, Dwarf_Attribute at, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_CU cu;
	int ret;

	assert(at->at_ld == NULL);
	assert(at->u[1].u8p != NULL);
	assert(at->u[0].u64 > 0);

	cu = die->die_cu;
	assert(cu != NULL);

	dbg = cu->cu_dbg;
	assert(dbg != NULL);

	ret = _dwarf_loc_fill_locexpr(dbg, &at->at_ld, at->u[1].u8p,
	    at->u[0].u64, cu->cu_pointer_size, cu->cu_length_size == 4 ? 4 : 8,
	    cu->cu_version, error);

	return (ret);
}