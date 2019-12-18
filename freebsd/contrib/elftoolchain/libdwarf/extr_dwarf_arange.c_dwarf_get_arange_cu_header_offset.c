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
struct TYPE_6__ {int /*<<< orphan*/  as_cu_offset; TYPE_1__* as_cu; } ;
struct TYPE_5__ {int /*<<< orphan*/ * cu_dbg; } ;
typedef  int /*<<< orphan*/  Dwarf_Off ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_ArangeSet ;
typedef  TYPE_3__* Dwarf_Arange ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DW_DLE_ARGUMENT ; 
 int DW_DLV_ERROR ; 
 int DW_DLV_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
dwarf_get_arange_cu_header_offset(Dwarf_Arange ar, Dwarf_Off *ret_offset,
    Dwarf_Error *error)
{
	Dwarf_ArangeSet as;

	if (ar == NULL) {
		DWARF_SET_ERROR(NULL, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	as = ar->ar_as;
	assert(as != NULL);

	if (ret_offset == NULL) {
		DWARF_SET_ERROR(as->as_cu->cu_dbg, error, DW_DLE_ARGUMENT);
		return (DW_DLV_ERROR);
	}

	*ret_offset = as->as_cu_offset;

	return (DW_DLV_OK);
}