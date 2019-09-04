#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {scalar_t__ cpu_tlb_invalid; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int PMAP_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PMAP_TRACE (int) ; 
 int /*<<< orphan*/  PMAP__UPDATE_INTERRUPT ; 
 TYPE_1__* current_cpu_datap () ; 
 int /*<<< orphan*/  process_pmap_updates () ; 

void
pmap_update_interrupt(void)
{
        PMAP_TRACE(PMAP_CODE(PMAP__UPDATE_INTERRUPT) | DBG_FUNC_START);

	if (current_cpu_datap()->cpu_tlb_invalid)
		process_pmap_updates();

        PMAP_TRACE(PMAP_CODE(PMAP__UPDATE_INTERRUPT) | DBG_FUNC_END);
}