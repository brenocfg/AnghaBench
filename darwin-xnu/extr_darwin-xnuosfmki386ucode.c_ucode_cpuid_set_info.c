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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 scalar_t__ AVX ; 
 scalar_t__ AVX512 ; 
 int AVX512_XMASK ; 
 int AVX_XMASK ; 
 int CR4_OSXSAVE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  XCR0 ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cpuid_set_info () ; 
 scalar_t__ fpu_capability ; 
 int get_cr4 () ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int xgetbv (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xsetbv (int,int) ; 

__attribute__((used)) static void
ucode_cpuid_set_info(void)
{
	uint64_t saved_xcr0, dest_xcr0;
	int need_xcr0_restore = 0;
	boolean_t intrs_enabled = ml_set_interrupts_enabled(FALSE);

	/*
	 * Before we cache the CPUID information, we must configure XCR0 with the maximal set of
	 * features to ensure the save area returned in the xsave leaf is correctly-sized.
	 *
	 * Since we are guaranteed that init_fpu() has already happened, we can use state
	 * variables set there that were already predicated on the presence of explicit
	 * boot-args enables/disables.
	 */

	if (fpu_capability == AVX512 || fpu_capability == AVX) {
		saved_xcr0 = xgetbv(XCR0);
		dest_xcr0 = (fpu_capability == AVX512) ? AVX512_XMASK : AVX_XMASK;
		assert((get_cr4() & CR4_OSXSAVE) != 0);
		if (saved_xcr0 != dest_xcr0) {
			need_xcr0_restore = 1;
			xsetbv(dest_xcr0 >> 32, dest_xcr0 & 0xFFFFFFFFUL);
		}
	}

	cpuid_set_info();

	if (need_xcr0_restore) {
		xsetbv(saved_xcr0 >> 32, saved_xcr0 & 0xFFFFFFFFUL);
	}

	ml_set_interrupts_enabled(intrs_enabled);
}