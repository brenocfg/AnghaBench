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
typedef  int /*<<< orphan*/  u32 ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FPE_FLTDIV ; 
 int /*<<< orphan*/  FPE_FLTINV ; 
 int /*<<< orphan*/  FPE_FLTOVF ; 
 int /*<<< orphan*/  FPE_FLTRES ; 
 int /*<<< orphan*/  FPE_FLTUND ; 
 int /*<<< orphan*/  FPSCR ; 
 int /*<<< orphan*/  FPSCR_DZC ; 
 int /*<<< orphan*/  FPSCR_DZE ; 
 int /*<<< orphan*/  FPSCR_IOC ; 
 int /*<<< orphan*/  FPSCR_IOE ; 
 int /*<<< orphan*/  FPSCR_IXC ; 
 int /*<<< orphan*/  FPSCR_IXE ; 
 int /*<<< orphan*/  FPSCR_OFC ; 
 int /*<<< orphan*/  FPSCR_OFE ; 
 int /*<<< orphan*/  FPSCR_UFC ; 
 int /*<<< orphan*/  FPSCR_UFE ; 
 int /*<<< orphan*/  RAISE (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VFP_EXCEPTION_ERROR ; 
 int /*<<< orphan*/  fmxr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vfp_raise_sigfpe (int,struct pt_regs*) ; 

__attribute__((used)) static void vfp_raise_exceptions(u32 exceptions, u32 inst, u32 fpscr, struct pt_regs *regs)
{
	int si_code = 0;

	pr_debug("VFP: raising exceptions %08x\n", exceptions);

	if (exceptions == VFP_EXCEPTION_ERROR) {
		vfp_panic("unhandled bounce", inst);
		vfp_raise_sigfpe(0, regs);
		return;
	}

	/*
	 * Update the FPSCR with the additional exception flags.
	 * Comparison instructions always return at least one of
	 * these flags set.
	 */
	fpscr |= exceptions;

	fmxr(FPSCR, fpscr);

#define RAISE(stat,en,sig)				\
	if (exceptions & stat && fpscr & en)		\
		si_code = sig;

	/*
	 * These are arranged in priority order, least to highest.
	 */
	RAISE(FPSCR_DZC, FPSCR_DZE, FPE_FLTDIV);
	RAISE(FPSCR_IXC, FPSCR_IXE, FPE_FLTRES);
	RAISE(FPSCR_UFC, FPSCR_UFE, FPE_FLTUND);
	RAISE(FPSCR_OFC, FPSCR_OFE, FPE_FLTOVF);
	RAISE(FPSCR_IOC, FPSCR_IOE, FPE_FLTINV);

	if (si_code)
		vfp_raise_sigfpe(si_code, regs);
}