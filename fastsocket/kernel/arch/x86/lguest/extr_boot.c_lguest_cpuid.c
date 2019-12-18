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
 int /*<<< orphan*/  native_cpuid (unsigned int*,unsigned int*,unsigned int*,unsigned int*) ; 

__attribute__((used)) static void lguest_cpuid(unsigned int *ax, unsigned int *bx,
			 unsigned int *cx, unsigned int *dx)
{
	int function = *ax;

	native_cpuid(ax, bx, cx, dx);
	switch (function) {
	/*
	 * CPUID 0 gives the highest legal CPUID number (and the ID string).
	 * We futureproof our code a little by sticking to known CPUID values.
	 */
	case 0:
		if (*ax > 5)
			*ax = 5;
		break;

	/*
	 * CPUID 1 is a basic feature request.
	 *
	 * CX: we only allow kernel to see SSE3, CMPXCHG16B and SSSE3
	 * DX: SSE, SSE2, FXSR, MMX, CMOV, CMPXCHG8B, TSC, FPU and PAE.
	 */
	case 1:
		*cx &= 0x00002201;
		*dx &= 0x07808151;
		/*
		 * The Host can do a nice optimization if it knows that the
		 * kernel mappings (addresses above 0xC0000000 or whatever
		 * PAGE_OFFSET is set to) haven't changed.  But Linux calls
		 * flush_tlb_user() for both user and kernel mappings unless
		 * the Page Global Enable (PGE) feature bit is set.
		 */
		*dx |= 0x00002000;
		/*
		 * We also lie, and say we're family id 5.  6 or greater
		 * leads to a rdmsr in early_init_intel which we can't handle.
		 * Family ID is returned as bits 8-12 in ax.
		 */
		*ax &= 0xFFFFF0FF;
		*ax |= 0x00000500;
		break;
	/*
	 * 0x80000000 returns the highest Extended Function, so we futureproof
	 * like we do above by limiting it to known fields.
	 */
	case 0x80000000:
		if (*ax > 0x80000008)
			*ax = 0x80000008;
		break;

	/*
	 * PAE systems can mark pages as non-executable.  Linux calls this the
	 * NX bit.  Intel calls it XD (eXecute Disable), AMD EVP (Enhanced
	 * Virus Protection).  We just switch turn if off here, since we don't
	 * support it.
	 */
	case 0x80000001:
		*dx &= ~(1 << 20);
		break;
	}
}