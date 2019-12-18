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
struct set_mtrr_context {int /*<<< orphan*/  flags; int /*<<< orphan*/  cr4val; int /*<<< orphan*/  ccr3; int /*<<< orphan*/  deftype_hi; int /*<<< orphan*/  deftype_lo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CYRIX ; 
 int /*<<< orphan*/  MSR_MTRRdefType ; 
 scalar_t__ cpu_has_pge ; 
 scalar_t__ is_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_restore (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_wrmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int read_cr0 () ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ use_intel () ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (int) ; 
 int /*<<< orphan*/  write_cr4 (int /*<<< orphan*/ ) ; 

void set_mtrr_done(struct set_mtrr_context *ctxt)
{
	if (use_intel() || is_cpu(CYRIX)) {

		/* Flush caches and TLBs */
		wbinvd();

		/* Restore MTRRdefType */
		if (use_intel()) {
			/* Intel (P6) standard MTRRs */
			mtrr_wrmsr(MSR_MTRRdefType, ctxt->deftype_lo,
				   ctxt->deftype_hi);
		} else {
			/*
			 * Cyrix ARRs -
			 * everything else was excluded at the top
			 */
			setCx86(CX86_CCR3, ctxt->ccr3);
		}

		/* Enable caches */
		write_cr0(read_cr0() & 0xbfffffff);

		/* Restore value of CR4 */
		if (cpu_has_pge)
			write_cr4(ctxt->cr4val);
	}
	/* Re-enable interrupts locally (if enabled previously) */
	local_irq_restore(ctxt->flags);
}