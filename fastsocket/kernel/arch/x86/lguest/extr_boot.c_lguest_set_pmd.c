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
typedef  int /*<<< orphan*/  pmd_t ;

/* Variables and functions */
 int /*<<< orphan*/  LHCALL_SET_PGD ; 
 int PAGE_MASK ; 
 int PAGE_SIZE ; 
 int __pa (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lazy_hcall2 (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  native_set_pmd (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_set_pmd(pmd_t *pmdp, pmd_t pmdval)
{
	native_set_pmd(pmdp, pmdval);
	lazy_hcall2(LHCALL_SET_PGD, __pa(pmdp) & PAGE_MASK,
		   (__pa(pmdp) & (PAGE_SIZE - 1)) / sizeof(pmd_t));
}