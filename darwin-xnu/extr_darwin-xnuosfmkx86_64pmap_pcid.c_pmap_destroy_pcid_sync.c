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
typedef  TYPE_1__* pmap_t ;
struct TYPE_4__ {scalar_t__* pmap_pcid_cpus; } ;

/* Variables and functions */
 scalar_t__ FALSE ; 
 scalar_t__ PMAP_PCID_INVALID_PCID ; 
 int PMAP_PCID_MAX_CPUS ; 
 scalar_t__ get_preemption_level () ; 
 scalar_t__ ml_get_interrupts_enabled () ; 
 int /*<<< orphan*/  pmap_assert (int) ; 
 int /*<<< orphan*/  pmap_pcid_deallocate_pcid (int,TYPE_1__*) ; 

void	pmap_destroy_pcid_sync(pmap_t p) {
	int i;
	pmap_assert(ml_get_interrupts_enabled() == FALSE || get_preemption_level() !=0);
	for (i = 0; i < PMAP_PCID_MAX_CPUS; i++)
		if (p->pmap_pcid_cpus[i] != PMAP_PCID_INVALID_PCID)
			pmap_pcid_deallocate_pcid(i, p);
}