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
struct TYPE_3__ {int /*<<< orphan*/  dbgp_drslist; void* dbgp_drspos; int /*<<< orphan*/  dbgp_seclist; void* dbgp_secpos; } ;
typedef  TYPE_1__* Dwarf_P_Debug ;

/* Variables and functions */
 void* STAILQ_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
dwarf_reset_section_bytes(Dwarf_P_Debug dbg)
{

	assert(dbg != NULL);

	dbg->dbgp_secpos = STAILQ_FIRST(&dbg->dbgp_seclist);
	dbg->dbgp_drspos = STAILQ_FIRST(&dbg->dbgp_drslist);
}