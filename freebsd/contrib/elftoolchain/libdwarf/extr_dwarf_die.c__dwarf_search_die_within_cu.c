#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cu_next_offset; int /*<<< orphan*/  cu_dwarf_size; } ;
typedef  int /*<<< orphan*/  Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_1__* Dwarf_CU ;

/* Variables and functions */
 int _dwarf_die_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int
_dwarf_search_die_within_cu(Dwarf_Debug dbg, Dwarf_Section *s, Dwarf_CU cu,
    Dwarf_Off offset, Dwarf_Die *ret_die, Dwarf_Error *error)
{

	assert(dbg != NULL && cu != NULL && ret_die != NULL);

	return (_dwarf_die_parse(dbg, s, cu, cu->cu_dwarf_size,
	    offset, cu->cu_next_offset, ret_die, 0, error));
}