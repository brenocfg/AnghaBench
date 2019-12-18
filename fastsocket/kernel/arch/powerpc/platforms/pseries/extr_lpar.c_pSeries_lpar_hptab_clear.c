#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  HPTE_V_1TB_SEG ; 
 unsigned long HPTE_V_VRMA_MASK ; 
 int /*<<< orphan*/  H_ANDCOND ; 
 long H_NOT_FOUND ; 
 long plpar_pte_read_raw (int /*<<< orphan*/ ,unsigned long,unsigned long*,unsigned long*) ; 
 long plpar_pte_remove_raw (int /*<<< orphan*/ ,unsigned long,int /*<<< orphan*/ ,unsigned long*,unsigned long*) ; 
 unsigned long ppc64_pft_size ; 

__attribute__((used)) static void pSeries_lpar_hptab_clear(void)
{
	unsigned long size_bytes = 1UL << ppc64_pft_size;
	unsigned long hpte_count = size_bytes >> 4;
	unsigned long dummy1, dummy2, dword0;
	long lpar_rc;
	unsigned long i;

	/* TODO: Use bulk call */
	for (i = 0; i < hpte_count; i++) {
		/* dont remove HPTEs with VRMA mappings */
		lpar_rc = plpar_pte_remove_raw(H_ANDCOND, i, HPTE_V_1TB_SEG,
						&dummy1, &dummy2);
		if (lpar_rc == H_NOT_FOUND) {
			lpar_rc = plpar_pte_read_raw(0, i, &dword0, &dummy1);
			if (!lpar_rc && ((dword0 & HPTE_V_VRMA_MASK)
				!= HPTE_V_VRMA_MASK))
				/* Can be hpte for 1TB Seg. So remove it */
				plpar_pte_remove_raw(0, i, 0, &dummy1, &dummy2);
		}
	}
}