#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  entry ;
struct TYPE_12__ {scalar_t__ ab_entry; } ;
struct TYPE_11__ {int cu_abbrev_loaded; scalar_t__ cu_abbrev_offset_cur; int /*<<< orphan*/  cu_dbg; int /*<<< orphan*/  cu_abbrev_hash; } ;
struct TYPE_10__ {scalar_t__ ds_size; } ;
typedef  scalar_t__ Dwarf_Unsigned ;
typedef  TYPE_1__ Dwarf_Section ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_2__* Dwarf_CU ;
typedef  TYPE_3__* Dwarf_Abbrev ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 int /*<<< orphan*/  HASH_FIND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,int,TYPE_3__*) ; 
 int _dwarf_abbrev_parse (int /*<<< orphan*/ ,TYPE_2__*,scalar_t__*,TYPE_3__**,int /*<<< orphan*/ *) ; 
 TYPE_1__* _dwarf_find_section (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ab_hh ; 

int
_dwarf_abbrev_find(Dwarf_CU cu, uint64_t entry, Dwarf_Abbrev *abp,
    Dwarf_Error *error)
{
	Dwarf_Abbrev ab;
	Dwarf_Section *ds;
	Dwarf_Unsigned offset;
	int ret;

	if (entry == 0)
		return (DW_DLE_NO_ENTRY);

	/* Check if the desired abbrev entry is already in the hash table. */
	HASH_FIND(ab_hh, cu->cu_abbrev_hash, &entry, sizeof(entry), ab);
	if (ab != NULL) {
		*abp = ab;
		return (DW_DLE_NONE);
	}

	if (cu->cu_abbrev_loaded) {
		return (DW_DLE_NO_ENTRY);
	}

	/* Load and search the abbrev table. */
	ds = _dwarf_find_section(cu->cu_dbg, ".debug_abbrev");
	if (ds == NULL)
		return (DW_DLE_NO_ENTRY);

	offset = cu->cu_abbrev_offset_cur;
	while (offset < ds->ds_size) {
		ret = _dwarf_abbrev_parse(cu->cu_dbg, cu, &offset, &ab, error);
		if (ret != DW_DLE_NONE)
			return (ret);
		if (ab->ab_entry == entry) {
			cu->cu_abbrev_offset_cur = offset;
			*abp = ab;
			return (DW_DLE_NONE);
		}
		if (ab->ab_entry == 0) {
			cu->cu_abbrev_offset_cur = offset;
			cu->cu_abbrev_loaded = 1;
			break;
		}
	}

	return (DW_DLE_NO_ENTRY);
}