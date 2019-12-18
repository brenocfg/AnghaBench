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
struct set_mtrr_context {int deftype_lo; int ccr3; int /*<<< orphan*/  deftype_hi; } ;

/* Variables and functions */
 int /*<<< orphan*/  CX86_CCR3 ; 
 int /*<<< orphan*/  CYRIX ; 
 int /*<<< orphan*/  MSR_MTRRdefType ; 
 scalar_t__ is_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtrr_wrmsr (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setCx86 (int /*<<< orphan*/ ,int) ; 
 scalar_t__ use_intel () ; 

void set_mtrr_cache_disable(struct set_mtrr_context *ctxt)
{
	if (use_intel()) {
		/* Disable MTRRs, and set the default type to uncached */
		mtrr_wrmsr(MSR_MTRRdefType, ctxt->deftype_lo & 0xf300UL,
		      ctxt->deftype_hi);
	} else {
		if (is_cpu(CYRIX)) {
			/* Cyrix ARRs - everything else were excluded at the top */
			setCx86(CX86_CCR3, (ctxt->ccr3 & 0x0f) | 0x10);
		}
	}
}