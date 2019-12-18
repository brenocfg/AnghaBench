#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* ar_as; } ;
struct TYPE_6__ {TYPE_1__* as_cu; } ;
struct TYPE_5__ {int /*<<< orphan*/  cu_1st_offset; int /*<<< orphan*/ * cu_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_CU ;
typedef  TYPE_2__* Dwarf_ArangeSet ;
typedef  TYPE_3__* Dwarf_Arange ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_cu_die_offset(Dwarf_Arange ar, Dwarf_Off *ret_offset,
    Dwarf_Error *error)
{
	Dwarf_CU cu;
	Dwarf_ArangeSet as;

	if (ar == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	as = ar->ar_as;
	assert(as != NULL);
	cu = as->as_cu;
	assert(cu != NULL);

	if (ret_offset == NULL) {
		DWARF_SET_ERROR(cu->cu_dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*ret_offset = cu->cu_1st_offset;

	return (DW_DLV_OK);
}