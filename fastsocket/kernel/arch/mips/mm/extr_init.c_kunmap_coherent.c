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
 int /*<<< orphan*/  ENTER_CRITICAL (unsigned long) ; 
 int /*<<< orphan*/  EXIT_CRITICAL (unsigned long) ; 
 unsigned long UNIQUE_ENTRYHI (unsigned int) ; 
 int /*<<< orphan*/  dec_preempt_count () ; 
 int /*<<< orphan*/  mtc0_tlbw_hazard () ; 
 int /*<<< orphan*/  preempt_check_resched () ; 
 unsigned long read_c0_entryhi () ; 
 unsigned int read_c0_wired () ; 
 int /*<<< orphan*/  tlb_write_indexed () ; 
 int /*<<< orphan*/  tlbw_use_hazard () ; 
 int /*<<< orphan*/  write_c0_entryhi (unsigned long) ; 
 int /*<<< orphan*/  write_c0_entrylo0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_entrylo1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_c0_index (unsigned int) ; 
 int /*<<< orphan*/  write_c0_wired (unsigned int) ; 

void kunmap_coherent(void)
{
#ifndef CONFIG_MIPS_MT_SMTC
	unsigned int wired;
	unsigned long flags, old_ctx;

	ENTER_CRITICAL(flags);
	old_ctx = read_c0_entryhi();
	wired = read_c0_wired() - 1;
	write_c0_wired(wired);
	write_c0_index(wired);
	write_c0_entryhi(UNIQUE_ENTRYHI(wired));
	write_c0_entrylo0(0);
	write_c0_entrylo1(0);
	mtc0_tlbw_hazard();
	tlb_write_indexed();
	tlbw_use_hazard();
	write_c0_entryhi(old_ctx);
	EXIT_CRITICAL(flags);
#endif
	dec_preempt_count();
	preempt_check_resched();
}