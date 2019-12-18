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
typedef  TYPE_1__* pmap_t ;
typedef  int /*<<< orphan*/  pcid_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pmap_pcid_cpus; } ;

/* Variables and functions */
 int /*<<< orphan*/  PMAP_PCID_INVALID_PCID ; 
 int /*<<< orphan*/  pmap_assert (int) ; 
 unsigned int real_ncpus ; 

void pmap_pcid_initialize(pmap_t p) {
	unsigned i;
	unsigned nc = sizeof(p->pmap_pcid_cpus)/sizeof(pcid_t);

	pmap_assert(nc >= real_ncpus);
	for (i = 0; i < nc; i++) {
		p->pmap_pcid_cpus[i] = PMAP_PCID_INVALID_PCID;
		/* We assume here that the coherency vector is zeroed by
		 * pmap_create
		 */
	}
}