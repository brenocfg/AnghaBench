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
 int /*<<< orphan*/  LHCALL_FLUSH_TLB ; 
 scalar_t__ cr3_changed ; 
 int /*<<< orphan*/  lazy_hcall1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  native_set_pte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lguest_set_pte(pte_t *ptep, pte_t pteval)
{
	native_set_pte(ptep, pteval);
	if (cr3_changed)
		lazy_hcall1(LHCALL_FLUSH_TLB, 1);
}