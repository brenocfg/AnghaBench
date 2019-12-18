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
struct TYPE_3__ {scalar_t__ dbg_mode; int /*<<< orphan*/  dbg_strtab; } ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 scalar_t__ DW_DLC_RDWR ; 
 scalar_t__ DW_DLC_WRITE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 

void
_dwarf_strtab_cleanup(Dwarf_Debug dbg)
{

	assert(dbg != NULL);

	if (dbg->dbg_mode == DW_DLC_RDWR || dbg->dbg_mode == DW_DLC_WRITE)
		free(dbg->dbg_strtab);
}