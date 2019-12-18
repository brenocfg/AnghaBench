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
struct hstate {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  hugepd_t ;

/* Variables and functions */
 int PTRS_PER_HUGEPTE (int) ; 
 unsigned int huge_page_shift (struct hstate*) ; 
 int /*<<< orphan*/ * hugepd_page (int /*<<< orphan*/ ) ; 
 int shift_to_mmu_psize (unsigned int) ; 

__attribute__((used)) static inline pte_t *hugepte_offset(hugepd_t *hpdp, unsigned long addr,
				    struct hstate *hstate)
{
	unsigned int shift = huge_page_shift(hstate);
	int psize = shift_to_mmu_psize(shift);
	unsigned long idx = ((addr >> shift) & (PTRS_PER_HUGEPTE(psize)-1));
	pte_t *dir = hugepd_page(*hpdp);

	return dir + idx;
}