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
struct lg_cpu {int dummy; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 unsigned long PAGE_SHIFT ; 
 int _PAGE_PRESENT ; 
 int pgd_flags (int /*<<< orphan*/ ) ; 
 unsigned long pgd_pfn (int /*<<< orphan*/ ) ; 
 int pte_index (unsigned long) ; 

__attribute__((used)) static unsigned long gpte_addr(struct lg_cpu *cpu,
				pgd_t gpgd, unsigned long vaddr)
{
	unsigned long gpage = pgd_pfn(gpgd) << PAGE_SHIFT;

	BUG_ON(!(pgd_flags(gpgd) & _PAGE_PRESENT));
	return gpage + pte_index(vaddr) * sizeof(pte_t);
}