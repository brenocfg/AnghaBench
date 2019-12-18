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
 int FP_EX_DIVZERO ; 
 int FP_EX_INEXACT ; 
 int FP_EX_INVALID ; 
 int FP_EX_OVERFLOW ; 
 int FP_EX_UNDERFLOW ; 
 long FSR_AEXC_SHIFT ; 
 unsigned long FSR_CEXC_MASK ; 
 long FSR_CEXC_SHIFT ; 
 unsigned long FSR_TEM_MASK ; 
 long FSR_TEM_SHIFT ; 

__attribute__((used)) static inline int record_exception(unsigned long *pfsr, int eflag)
{
	unsigned long fsr = *pfsr;
	int would_trap;

	/* Determine if this exception would have generated a trap. */
	would_trap = (fsr & ((long)eflag << FSR_TEM_SHIFT)) != 0UL;

	/* If trapping, we only want to signal one bit. */
	if (would_trap != 0) {
		eflag &= ((fsr & FSR_TEM_MASK) >> FSR_TEM_SHIFT);
		if ((eflag & (eflag - 1)) != 0) {
			if (eflag & FP_EX_INVALID)
				eflag = FP_EX_INVALID;
			else if (eflag & FP_EX_OVERFLOW)
				eflag = FP_EX_OVERFLOW;
			else if (eflag & FP_EX_UNDERFLOW)
				eflag = FP_EX_UNDERFLOW;
			else if (eflag & FP_EX_DIVZERO)
				eflag = FP_EX_DIVZERO;
			else if (eflag & FP_EX_INEXACT)
				eflag = FP_EX_INEXACT;
		}
	}

	/* Set CEXC, here is the rule:
	 *
	 *    In general all FPU ops will set one and only one
	 *    bit in the CEXC field, this is always the case
	 *    when the IEEE exception trap is enabled in TEM.
	 */
	fsr &= ~(FSR_CEXC_MASK);
	fsr |= ((long)eflag << FSR_CEXC_SHIFT);

	/* Set the AEXC field, rule is:
	 *
	 *    If a trap would not be generated, the
	 *    CEXC just generated is OR'd into the
	 *    existing value of AEXC.
	 */
	if (would_trap == 0)
		fsr |= ((long)eflag << FSR_AEXC_SHIFT);

	/* If trapping, indicate fault trap type IEEE. */
	if (would_trap != 0)
		fsr |= (1UL << 14);

	*pfsr = fsr;

	return (would_trap ? 0 : 1);
}