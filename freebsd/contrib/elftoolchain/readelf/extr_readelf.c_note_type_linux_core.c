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
 char const* note_type_unknown (unsigned int) ; 

__attribute__((used)) static const char *
note_type_linux_core(unsigned int nt)
{
	switch (nt) {
	case 1: return "NT_PRSTATUS (Process status)";
	case 2: return "NT_FPREGSET (Floating point information)";
	case 3: return "NT_PRPSINFO (Process information)";
	case 4: return "NT_TASKSTRUCT (Task structure)";
	case 6: return "NT_AUXV (Auxiliary vector)";
	case 10: return "NT_PSTATUS (Linux process status)";
	case 12: return "NT_FPREGS (Linux floating point regset)";
	case 13: return "NT_PSINFO (Linux process information)";
	case 16: return "NT_LWPSTATUS (Linux lwpstatus_t type)";
	case 17: return "NT_LWPSINFO (Linux lwpinfo_t type)";
	case 18: return "NT_WIN32PSTATUS (win32_pstatus structure)";
	case 0x100: return "NT_PPC_VMX (ppc Altivec registers)";
	case 0x102: return "NT_PPC_VSX (ppc VSX registers)";
	case 0x202: return "NT_X86_XSTATE (x86 XSAVE extended state)";
	case 0x300: return "NT_S390_HIGH_GPRS (s390 upper register halves)";
	case 0x301: return "NT_S390_TIMER (s390 timer register)";
	case 0x302: return "NT_S390_TODCMP (s390 TOD comparator register)";
	case 0x303: return "NT_S390_TODPREG (s390 TOD programmable register)";
	case 0x304: return "NT_S390_CTRS (s390 control registers)";
	case 0x305: return "NT_S390_PREFIX (s390 prefix register)";
	case 0x400: return "NT_ARM_VFP (arm VFP registers)";
	case 0x46494c45UL: return "NT_FILE (mapped files)";
	case 0x46E62B7FUL: return "NT_PRXFPREG (Linux user_xfpregs structure)";
	case 0x53494749UL: return "NT_SIGINFO (siginfo_t data)";
	default: return (note_type_unknown(nt));
	}
}