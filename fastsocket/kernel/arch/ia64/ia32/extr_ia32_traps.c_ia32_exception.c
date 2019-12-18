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
struct siginfo {unsigned long si_isr; void* si_signo; void* si_code; scalar_t__ si_flags; scalar_t__ si_imm; scalar_t__ si_errno; } ;
struct pt_regs {int dummy; } ;

/* Variables and functions */
 void* BUS_ADRALN ; 
 void* FPE_FLTDIV ; 
 void* FPE_FLTINV ; 
 void* FPE_FLTOVF ; 
 void* FPE_FLTRES ; 
 void* FPE_FLTUND ; 
 void* FPE_INTDIV ; 
 void* ILL_ILLOPN ; 
 void* SIGFPE ; 
 void* SIGILL ; 
 void* SIGSEGV ; 
 void* SIGTRAP ; 
 void* TRAP_BRANCH ; 
 void* TRAP_BRKPT ; 
 void* TRAP_TRACE ; 
 int /*<<< orphan*/  _IA64_REG_AR_FCR ; 
 int /*<<< orphan*/  _IA64_REG_AR_FSR ; 
 scalar_t__ __ISR_VALID ; 
 int /*<<< orphan*/  current ; 
 int /*<<< orphan*/  force_sig_info (void*,struct siginfo*,int /*<<< orphan*/ ) ; 
 unsigned long ia64_getreg (int /*<<< orphan*/ ) ; 

int
ia32_exception (struct pt_regs *regs, unsigned long isr)
{
	struct siginfo siginfo;

	/* initialize these fields to avoid leaking kernel bits to user space: */
	siginfo.si_errno = 0;
	siginfo.si_flags = 0;
	siginfo.si_isr = 0;
	siginfo.si_imm = 0;
	switch ((isr >> 16) & 0xff) {
	      case 1:
	      case 2:
		siginfo.si_signo = SIGTRAP;
		if (isr == 0)
			siginfo.si_code = TRAP_TRACE;
		else if (isr & 0x4)
			siginfo.si_code = TRAP_BRANCH;
		else
			siginfo.si_code = TRAP_BRKPT;
		break;

	      case 3:
		siginfo.si_signo = SIGTRAP;
		siginfo.si_code = TRAP_BRKPT;
		break;

	      case 0:	/* Divide fault */
		siginfo.si_signo = SIGFPE;
		siginfo.si_code = FPE_INTDIV;
		break;

	      case 4:	/* Overflow */
	      case 5:	/* Bounds fault */
		siginfo.si_signo = SIGFPE;
		siginfo.si_code = 0;
		break;

	      case 6:	/* Invalid Op-code */
		siginfo.si_signo = SIGILL;
		siginfo.si_code = ILL_ILLOPN;
		break;

	      case 7:	/* FP DNA */
	      case 8:	/* Double Fault */
	      case 9:	/* Invalid TSS */
	      case 11:	/* Segment not present */
	      case 12:	/* Stack fault */
	      case 13:	/* General Protection Fault */
		siginfo.si_signo = SIGSEGV;
		siginfo.si_code = 0;
		break;

	      case 16:	/* Pending FP error */
		{
			unsigned long fsr, fcr;

			fsr = ia64_getreg(_IA64_REG_AR_FSR);
			fcr = ia64_getreg(_IA64_REG_AR_FCR);

			siginfo.si_signo = SIGFPE;
			/*
			 * (~cwd & swd) will mask out exceptions that are not set to unmasked
			 * status.  0x3f is the exception bits in these regs, 0x200 is the
			 * C1 reg you need in case of a stack fault, 0x040 is the stack
			 * fault bit.  We should only be taking one exception at a time,
			 * so if this combination doesn't produce any single exception,
			 * then we have a bad program that isn't synchronizing its FPU usage
			 * and it will suffer the consequences since we won't be able to
			 * fully reproduce the context of the exception
			 */
			siginfo.si_isr = isr;
			siginfo.si_flags = __ISR_VALID;
			switch(((~fcr) & (fsr & 0x3f)) | (fsr & 0x240)) {
				case 0x000:
				default:
					siginfo.si_code = 0;
					break;
				case 0x001: /* Invalid Op */
				case 0x040: /* Stack Fault */
				case 0x240: /* Stack Fault | Direction */
					siginfo.si_code = FPE_FLTINV;
					break;
				case 0x002: /* Denormalize */
				case 0x010: /* Underflow */
					siginfo.si_code = FPE_FLTUND;
					break;
				case 0x004: /* Zero Divide */
					siginfo.si_code = FPE_FLTDIV;
					break;
				case 0x008: /* Overflow */
					siginfo.si_code = FPE_FLTOVF;
					break;
				case 0x020: /* Precision */
					siginfo.si_code = FPE_FLTRES;
					break;
			}

			break;
		}

	      case 17:	/* Alignment check */
		siginfo.si_signo = SIGSEGV;
		siginfo.si_code = BUS_ADRALN;
		break;

	      case 19:	/* SSE Numeric error */
		siginfo.si_signo = SIGFPE;
		siginfo.si_code = 0;
		break;

	      default:
		return -1;
	}
	force_sig_info(siginfo.si_signo, &siginfo, current);
	return 0;
}