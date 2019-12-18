#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ dbg_mode; } ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
 scalar_t__ DW_DLC_READ ; 
 scalar_t__ DW_DLC_WRITE ; 
 int /*<<< orphan*/  _dwarf_consumer_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  _dwarf_producer_deinit (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

void
_dwarf_deinit(Dwarf_Debug dbg)
{

	assert(dbg != NULL);

	if (dbg->dbg_mode == DW_DLC_READ)
		_dwarf_consumer_deinit(dbg);
	else if (dbg->dbg_mode == DW_DLC_WRITE)
		_dwarf_producer_deinit(dbg);
}