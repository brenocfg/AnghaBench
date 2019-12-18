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
typedef  int /*<<< orphan*/  s_ptype ;

/* Variables and functions */
#define  EM_ARM 144 
#define  PT_ARM_ARCHEXT 143 
#define  PT_ARM_EXIDX 142 
#define  PT_DYNAMIC 141 
#define  PT_GNU_EH_FRAME 140 
#define  PT_GNU_RELRO 139 
#define  PT_GNU_STACK 138 
 unsigned int PT_HIOS ; 
 unsigned int PT_HIPROC ; 
#define  PT_INTERP 137 
#define  PT_LOAD 136 
 unsigned int PT_LOOS ; 
 unsigned int PT_LOPROC ; 
#define  PT_NOTE 135 
#define  PT_NULL 134 
#define  PT_OPENBSD_BOOTDATA 133 
#define  PT_OPENBSD_RANDOMIZE 132 
#define  PT_OPENBSD_WXNEEDED 131 
#define  PT_PHDR 130 
#define  PT_SHLIB 129 
#define  PT_TLS 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
phdr_type(unsigned int mach, unsigned int ptype)
{
	static char s_ptype[32];

	if (ptype >= PT_LOPROC && ptype <= PT_HIPROC) {
		switch (mach) {
		case EM_ARM:
			switch (ptype) {
			case PT_ARM_ARCHEXT: return "ARM_ARCHEXT";
			case PT_ARM_EXIDX: return "ARM_EXIDX";
			}
			break;
		}
		snprintf(s_ptype, sizeof(s_ptype), "LOPROC+%#x",
		    ptype - PT_LOPROC);
		return (s_ptype);
	}

	switch (ptype) {
	case PT_NULL: return "NULL";
	case PT_LOAD: return "LOAD";
	case PT_DYNAMIC: return "DYNAMIC";
	case PT_INTERP: return "INTERP";
	case PT_NOTE: return "NOTE";
	case PT_SHLIB: return "SHLIB";
	case PT_PHDR: return "PHDR";
	case PT_TLS: return "TLS";
	case PT_GNU_EH_FRAME: return "GNU_EH_FRAME";
	case PT_GNU_STACK: return "GNU_STACK";
	case PT_GNU_RELRO: return "GNU_RELRO";
	case PT_OPENBSD_RANDOMIZE: return "OPENBSD_RANDOMIZE";
	case PT_OPENBSD_WXNEEDED: return "OPENBSD_WXNEEDED";
	case PT_OPENBSD_BOOTDATA: return "OPENBSD_BOOTDATA";
	default:
		if (ptype >= PT_LOOS && ptype <= PT_HIOS)
			snprintf(s_ptype, sizeof(s_ptype), "LOOS+%#x",
			    ptype - PT_LOOS);
		else
			snprintf(s_ptype, sizeof(s_ptype), "<unknown: %#x>",
			    ptype);
		return (s_ptype);
	}
}