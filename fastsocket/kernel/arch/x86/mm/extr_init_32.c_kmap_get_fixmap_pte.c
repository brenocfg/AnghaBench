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
typedef  int /*<<< orphan*/  pte_t ;

/* Variables and functions */
 int /*<<< orphan*/  pgd_offset_k (unsigned long) ; 
 int /*<<< orphan*/  pmd_offset (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * pte_offset_kernel (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  pud_offset (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static inline pte_t *kmap_get_fixmap_pte(unsigned long vaddr)
{
	return pte_offset_kernel(pmd_offset(pud_offset(pgd_offset_k(vaddr),
			vaddr), vaddr), vaddr);
}