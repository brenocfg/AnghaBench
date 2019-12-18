#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_15__ {int cu_pointer_size; int cu_length_size; int /*<<< orphan*/  cu_version; } ;
struct TYPE_14__ {scalar_t__ (* read ) (scalar_t__,scalar_t__*,int) ;} ;
struct TYPE_13__ {scalar_t__ ld_hipc; scalar_t__ ld_lopc; } ;
struct TYPE_12__ {scalar_t__ ds_size; scalar_t__ ds_data; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  int Dwarf_Signed ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  TYPE_2__ Dwarf_Locdesc ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_3__* Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_CU ;

/* Variables and functions */
 int /*<<< orphan*/  DWARF_SET_ERROR (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 int DW_DLE_DEBUG_LOC_SECTION_SHORT ; 
 int DW_DLE_NONE ; 
 int _dwarf_loc_fill_locdesc (TYPE_3__*,TYPE_2__*,scalar_t__,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__*,int) ; 
 scalar_t__ stub2 (scalar_t__,scalar_t__*,int) ; 
 int stub3 (scalar_t__,scalar_t__*,int) ; 

__attribute__((used)) static int
_dwarf_loclist_add_locdesc(Dwarf_Debug dbg, Dwarf_CU cu, Dwarf_Section *ds,
    Dwarf_Unsigned *off, Dwarf_Locdesc **ld, Dwarf_Signed *ldlen,
    Dwarf_Unsigned *total_len, Dwarf_Error *error)
{
	uint64_t start, end;
	int i, len, ret;

	if (total_len != NULL)
		*total_len = 0;

	for (i = 0; *off < ds->ds_size; i++) {
		start = dbg->read(ds->ds_data, off, cu->cu_pointer_size);
		end = dbg->read(ds->ds_data, off, cu->cu_pointer_size);
		if (ld != NULL) {
			ld[i]->ld_lopc = start;
			ld[i]->ld_hipc = end;
		}

		if (total_len != NULL)
			*total_len += 2 * cu->cu_pointer_size;

		/* Check if it is the end entry. */
		if (start == 0 && end ==0) {
			i++;
			break;
		}

		/* Check if it is base-select entry. */
		if ((cu->cu_pointer_size == 4 && start == ~0U) ||
		    (cu->cu_pointer_size == 8 && start == ~0ULL))
			continue;

		/* Otherwise it's normal entry. */
		len = dbg->read(ds->ds_data, off, 2);
		if (*off + len > ds->ds_size) {
			DWARF_SET_ERROR(dbg, error,
			    DW_DLE_DEBUG_LOC_SECTION_SHORT);
			return (DW_DLE_DEBUG_LOC_SECTION_SHORT);
		}

		if (total_len != NULL)
			*total_len += len;

		if (ld != NULL) {
			ret = _dwarf_loc_fill_locdesc(dbg, ld[i],
			    ds->ds_data + *off, len, cu->cu_pointer_size,
			    cu->cu_length_size == 4 ? 4 : 8, cu->cu_version,
			    error);
			if (ret != DW_DLE_NONE)
				return (ret);
		}

		*off += len;
	}

	if (ldlen != NULL)
		*ldlen = i;

	return (DW_DLE_NONE);
}