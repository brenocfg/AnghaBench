#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_4__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint64_t ;
typedef  TYPE_1__* pmap_t ;
struct TYPE_6__ {int cpu_pagezero_mapped; } ;
struct TYPE_5__ {int pagezero_accessible; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 TYPE_4__* current_cpu_datap () ; 
 TYPE_1__* current_pmap () ; 
 int /*<<< orphan*/  mp_disable_preemption () ; 
 int /*<<< orphan*/  mp_enable_preemption () ; 
 scalar_t__ pmap_pagezero_mitigation ; 
 scalar_t__ pmap_smap_enabled ; 

void pmap_advise_pagezero_range(pmap_t lpmap, uint64_t low_bound) {
#if DEVELOPMENT || DEBUG
	if (pmap_pagezero_mitigation == 0) {
		lpmap->pagezero_accessible = FALSE;
		return;
	}
#endif
	lpmap->pagezero_accessible = ((pmap_smap_enabled == FALSE) && (low_bound < 0x1000));
	if (lpmap == current_pmap()) {
		mp_disable_preemption();
		current_cpu_datap()->cpu_pagezero_mapped = lpmap->pagezero_accessible;
		mp_enable_preemption();
	}
}