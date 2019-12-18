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
typedef  int /*<<< orphan*/  pte_t ;
struct TYPE_3__ {int /*<<< orphan*/ * pmdv; } ;
typedef  TYPE_1__ pmd_t ;

/* Variables and functions */
 int PTRS_PER_PTE ; 
 unsigned long SRMMU_ET_PTD ; 
 int SRMMU_REAL_PTRS_PER_PTE ; 
 int __nocache_pa (unsigned long) ; 
 int /*<<< orphan*/  srmmu_set_pte (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void srmmu_pmd_set(pmd_t *pmdp, pte_t *ptep)
{
	unsigned long ptp;	/* Physical address, shifted right by 4 */
	int i;

	ptp = __nocache_pa((unsigned long) ptep) >> 4;
	for (i = 0; i < PTRS_PER_PTE/SRMMU_REAL_PTRS_PER_PTE; i++) {
		srmmu_set_pte((pte_t *)&pmdp->pmdv[i], SRMMU_ET_PTD | ptp);
		ptp += (SRMMU_REAL_PTRS_PER_PTE*sizeof(pte_t) >> 4);
	}
}