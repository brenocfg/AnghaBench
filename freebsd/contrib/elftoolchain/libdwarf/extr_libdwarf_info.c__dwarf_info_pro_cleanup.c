#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ dbg_mode; int /*<<< orphan*/  dbg_cu; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;
typedef  int /*<<< orphan*/ * Dwarf_CU ;

/* Variables and functions */
 scalar_t__ DW_DLC_WRITE ; 
 int /*<<< orphan*/ * STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  STAILQ_REMOVE (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _Dwarf_CU ; 
 int /*<<< orphan*/  _dwarf_abbrev_cleanup (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cu_next ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
_dwarf_info_pro_cleanup(Dwarf_P_Debug dbg)
{
	Dwarf_CU cu;

	assert(dbg != NULL && dbg->dbg_mode == DW_DLC_WRITE);

	cu = STAILQ_FIRST(&dbg->dbg_cu);
	if (cu != NULL) {
		STAILQ_REMOVE(&dbg->dbg_cu, cu, _Dwarf_CU, cu_next);
		_dwarf_abbrev_cleanup(cu);
		free(cu);
	}
}