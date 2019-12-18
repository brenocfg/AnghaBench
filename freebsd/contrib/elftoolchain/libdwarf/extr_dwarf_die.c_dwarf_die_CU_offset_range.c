#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ cu_length_size; scalar_t__ cu_length; scalar_t__ cu_offset; } ;
struct TYPE_4__ {TYPE_2__* die_cu; int /*<<< orphan*/ * die_dbg; } ;
typedef  scalar_t__ Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Die ;
typedef  int /*<<< orphan*/ * Dwarf_Debug ;
typedef  TYPE_2__* Dwarf_CU ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_die_CU_offset_range(Dwarf_Die die, Dwarf_Off *cu_offset,
    Dwarf_Off *cu_length, Dwarf_Error *error)
{
	Dwarf_Debug dbg;
	Dwarf_CU cu;

	dbg = die != NULL ? die->die_dbg : NULL;

	if (die == NULL || cu_offset == NULL || cu_length == NULL) {
		DWARF_SET_ERROR(dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	cu = die->die_cu;
	assert(cu != NULL);

	*cu_offset = cu->cu_offset;
	*cu_length = cu->cu_length + cu->cu_length_size;

	return (DW_DLV_OK);
}