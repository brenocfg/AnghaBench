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
struct set_mtrr_context {int cr4val; int /*<<< orphan*/  ccr3; int /*<<< orphan*/  deftype_hi; int /*<<< orphan*/  deftype_lo; int /*<<< orphan*/  flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CYRIX ; 
 int /*<<< orphan*/  MSR_MTRRdefType ; 
 unsigned int X86_CR0_CD ; 
 int X86_CR4_PGE ; 
 scalar_t__ cpu_has_pge ; 
 int /*<<< orphan*/  getCx86 (int /*<<< orphan*/ ) ; 
 scalar_t__ is_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  local_irq_save (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rdmsr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int read_cr0 () ; 
 int read_cr4 () ; 
 scalar_t__ use_intel () ; 
 int /*<<< orphan*/  wbinvd () ; 
 int /*<<< orphan*/  write_cr0 (unsigned int) ; 
 int /*<<< orphan*/  write_cr4 (int) ; 

void set_mtrr_prepare_save(struct set_mtrr_context *ctxt)
{
	unsigned int cr0;

	/* Disable interrupts locally */
	local_irq_save(ctxt->flags);

	if (use_intel() || is_cpu(CYRIX)) {

		/* Save value of CR4 and clear Page Global Enable (bit 7) */
		if (cpu_has_pge) {
			ctxt->cr4val = read_cr4();
			write_cr4(ctxt->cr4val & ~X86_CR4_PGE);
		}

		/*
		 * Disable and flush caches. Note that wbinvd flushes the TLBs
		 * as a side-effect
		 */
		cr0 = read_cr0() | X86_CR0_CD;
		wbinvd();
		write_cr0(cr0);
		wbinvd();

		if (use_intel()) {
			/* Save MTRR state */
			rdmsr(MSR_MTRRdefType, ctxt->deftype_lo, ctxt->deftype_hi);
		} else {
			/*
			 * Cyrix ARRs -
			 * everything else were excluded at the top
			 */
			ctxt->ccr3 = getCx86(CX86_CCR3);
		}
	}
}