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
struct TYPE_3__ {scalar_t__* pmap_pcid_cpus; } ;

/* Variables and functions */

void pmap_pcid_initialize_kernel(pmap_t p) {
	unsigned i;
	unsigned nc = sizeof(p->pmap_pcid_cpus)/sizeof(pcid_t);

	for (i = 0; i < nc; i++) {
		p->pmap_pcid_cpus[i] = 0;
		/* We assume here that the coherency vector is zeroed by
		 * pmap_create
		 */
	}
}