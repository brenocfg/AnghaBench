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
struct TYPE_4__ {int /*<<< orphan*/  dbg_cu; int /*<<< orphan*/ * dbg_cu_current; scalar_t__ dbg_info_off; scalar_t__ dbg_info_loaded; } ;
typedef  int /*<<< orphan*/  Dwarf_Error ;
typedef  TYPE_1__* Dwarf_Debug ;
typedef  int /*<<< orphan*/ * Dwarf_CU ;

/* Variables and functions */
 int DW_DLE_NONE ; 
 int DW_DLE_NO_ENTRY ; 
 void* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int _dwarf_info_load (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

int
_dwarf_info_first_cu(Dwarf_Debug dbg, Dwarf_Error *error)
{
	Dwarf_CU cu;
	int ret;

	assert(dbg->dbg_cu_current == NULL);
	cu = STAILQ_FIRST(&dbg->dbg_cu);
	if (cu != NULL) {
		dbg->dbg_cu_current = cu;
		return (DW_DLE_NONE);
	}

	if (dbg->dbg_info_loaded)
		return (DW_DLE_NO_ENTRY);

	dbg->dbg_info_off = 0;
	ret = _dwarf_info_load(dbg, 0, 1, error);
	if (ret != DW_DLE_NONE)
		return (ret);

	dbg->dbg_cu_current = STAILQ_FIRST(&dbg->dbg_cu);

	return (DW_DLE_NONE);
}