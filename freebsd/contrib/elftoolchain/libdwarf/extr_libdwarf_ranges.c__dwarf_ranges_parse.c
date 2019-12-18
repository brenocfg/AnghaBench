#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_12__ {int cu_pointer_size; } ;
struct TYPE_11__ {scalar_t__ (* read ) (int /*<<< orphan*/ ,scalar_t__*,int) ;} ;
struct TYPE_10__ {int /*<<< orphan*/  dwr_type; scalar_t__ dwr_addr2; scalar_t__ dwr_addr1; } ;
struct TYPE_9__ {scalar_t__ ds_size; int /*<<< orphan*/  ds_data; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  TYPE_2__ Dwarf_Ranges ;
typedef  TYPE_3__* Dwarf_Debug ;
typedef  TYPE_4__* Dwarf_CU ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int /*<<< orphan*/  DW_RANGES_ADDRESS_SELECTION ; 
 int /*<<< orphan*/  DW_RANGES_END ; 
 int /*<<< orphan*/  DW_RANGES_ENTRY ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,scalar_t__*,int) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,scalar_t__*,int) ; 

__attribute__((used)) static int
_dwarf_ranges_parse(Dwarf_Debug dbg, Dwarf_CU cu, Dwarf_Section *ds,
    uint64_t off, Dwarf_Ranges *rg, Dwarf_Unsigned *cnt)
{
	Dwarf_Unsigned start, end;
	int i;

	i = 0;
	while (off < ds->ds_size) {

		start = dbg->read(ds->ds_data, &off, cu->cu_pointer_size);
		end = dbg->read(ds->ds_data, &off, cu->cu_pointer_size);

		if (rg != NULL) {
			rg[i].dwr_addr1 = start;
			rg[i].dwr_addr2 = end;
			if (start == 0 && end == 0)
				rg[i].dwr_type = DW_RANGES_END;
			else if ((start == ~0U && cu->cu_pointer_size == 4) ||
			    (start == ~0ULL && cu->cu_pointer_size == 8))
				rg[i].dwr_type = DW_RANGES_ADDRESS_SELECTION;
			else
				rg[i].dwr_type = DW_RANGES_ENTRY;
		}

		i++;

		if (start == 0 && end == 0)
			break;
	}

	if (cnt != NULL)
		*cnt = i;

	return (DW_DLE_NONE);
}