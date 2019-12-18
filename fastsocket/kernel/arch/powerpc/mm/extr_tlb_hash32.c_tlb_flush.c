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
struct mmu_gather {int dummy; } ;

/* Variables and functions */
 scalar_t__ Hash ; 
 int /*<<< orphan*/  _tlbia () ; 
 int /*<<< orphan*/  pte_free_finish () ; 

void tlb_flush(struct mmu_gather *tlb)
{
	if (Hash == 0) {
		/*
		 * 603 needs to flush the whole TLB here since
		 * it doesn't use a hash table.
		 */
		_tlbia();
	}

	/* Push out batch of freed page tables */
	pte_free_finish();
}