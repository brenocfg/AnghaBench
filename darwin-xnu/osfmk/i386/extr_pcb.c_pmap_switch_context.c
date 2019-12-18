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
typedef  TYPE_2__* vm_map_t ;
typedef  TYPE_3__* thread_t ;
struct TYPE_12__ {TYPE_2__* map; } ;
struct TYPE_11__ {TYPE_1__* pmap; } ;
struct TYPE_10__ {scalar_t__ pagezero_accessible; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  PMAP_ACTIVATE_MAP (TYPE_2__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  PMAP_DEACTIVATE_MAP (TYPE_2__*,TYPE_3__*,int) ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  pmap_assert (int) ; 

__attribute__((used)) static inline void pmap_switch_context(thread_t ot, thread_t nt, int cnum) {
	pmap_assert(ml_get_interrupts_enabled() == FALSE);
	vm_map_t nmap = nt->map, omap = ot->map;
	if ((omap != nmap) || (nmap->pmap->pagezero_accessible)) {
		PMAP_DEACTIVATE_MAP(omap, ot, cnum);
		PMAP_ACTIVATE_MAP(nmap, nt, cnum);
	}
}