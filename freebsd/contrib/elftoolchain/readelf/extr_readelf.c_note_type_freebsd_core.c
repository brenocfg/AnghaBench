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
note_type_freebsd_core(unsigned int nt)
{
	switch (nt) {
	case 1: return "NT_PRSTATUS";
	case 2: return "NT_FPREGSET";
	case 3: return "NT_PRPSINFO";
	case 7: return "NT_THRMISC";
	case 8: return "NT_PROCSTAT_PROC";
	case 9: return "NT_PROCSTAT_FILES";
	case 10: return "NT_PROCSTAT_VMMAP";
	case 11: return "NT_PROCSTAT_GROUPS";
	case 12: return "NT_PROCSTAT_UMASK";
	case 13: return "NT_PROCSTAT_RLIMIT";
	case 14: return "NT_PROCSTAT_OSREL";
	case 15: return "NT_PROCSTAT_PSSTRINGS";
	case 16: return "NT_PROCSTAT_AUXV";
	case 17: return "NT_PTLWPINFO";
	case 0x202: return "NT_X86_XSTATE (x86 XSAVE extended state)";
	case 0x400: return "NT_ARM_VFP (arm VFP registers)";
	default: return (note_type_unknown(nt));
	}
}