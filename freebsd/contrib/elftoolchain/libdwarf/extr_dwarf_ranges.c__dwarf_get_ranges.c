#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int cu_pointer_size; } ;
struct TYPE_7__ {int rl_rglen; int /*<<< orphan*/ * rl_rgarray; } ;
typedef  int Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  int /*<<< orphan*/  Dwarf_Ranges ;
typedef  TYPE_1__* Dwarf_Rangelist ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  int /*<<< orphan*/  Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_CU ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 scalar_t__ DW_DLE_NO_ENTRY ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int _dwarf_ranges_add (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**,int /*<<< orphan*/ *) ; 
 scalar_t__ _dwarf_ranges_find (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
_dwarf_get_ranges(Dwarf_Debug dbg, Dwarf_CU cu, Dwarf_Off off,
    Dwarf_Ranges **ranges, Dwarf_Signed *ret_cnt, Dwarf_Unsigned *ret_byte_cnt,
    Dwarf_Error *error)
{
	Dwarf_Rangelist rl;
	int ret;

	assert(cu != NULL);
	if (_dwarf_ranges_find(dbg, off, &rl) == DW_DLE_NO_ENTRY) {
		ret = _dwarf_ranges_add(dbg, cu, off, &rl, error);
		if (ret != DW_DLE_NONE)
			return (DW_DLV_ERROR);
	}

	*ranges = rl->rl_rgarray;
	*ret_cnt = rl->rl_rglen;

	if (ret_byte_cnt != NULL)
		*ret_byte_cnt = cu->cu_pointer_size * rl->rl_rglen * 2;

	return (DW_DLV_OK);
}