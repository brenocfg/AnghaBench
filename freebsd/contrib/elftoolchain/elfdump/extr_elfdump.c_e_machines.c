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
typedef  int /*<<< orphan*/  machdesc ;

/* Variables and functions */
#define  EM_386 145 
#define  EM_68K 144 
#define  EM_860 143 
#define  EM_88K 142 
#define  EM_AARCH64 141 
#define  EM_ALPHA 140 
#define  EM_ARM 139 
#define  EM_IAMCU 138 
#define  EM_IA_64 137 
#define  EM_M32 136 
#define  EM_MIPS 135 
#define  EM_NONE 134 
#define  EM_PPC 133 
#define  EM_PPC64 132 
#define  EM_RISCV 131 
#define  EM_SPARC 130 
#define  EM_SPARCV9 129 
#define  EM_X86_64 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,unsigned int) ; 

__attribute__((used)) static const char *
e_machines(unsigned int mach)
{
	static char machdesc[64];

	switch (mach) {
	case EM_NONE:	return "EM_NONE";
	case EM_M32:	return "EM_M32";
	case EM_SPARC:	return "EM_SPARC";
	case EM_386:	return "EM_386";
	case EM_68K:	return "EM_68K";
	case EM_88K:	return "EM_88K";
	case EM_IAMCU:	return "EM_IAMCU";
	case EM_860:	return "EM_860";
	case EM_MIPS:	return "EM_MIPS";
	case EM_PPC:	return "EM_PPC";
	case EM_PPC64:	return "EM_PPC64";
	case EM_ARM:	return "EM_ARM";
	case EM_ALPHA:	return "EM_ALPHA (legacy)";
	case EM_SPARCV9:return "EM_SPARCV9";
	case EM_IA_64:	return "EM_IA_64";
	case EM_X86_64:	return "EM_X86_64";
	case EM_AARCH64:return "EM_AARCH64";
	case EM_RISCV:	return "EM_RISCV";
	}
	snprintf(machdesc, sizeof(machdesc),
	    "(unknown machine) -- type 0x%x", mach);
	return (machdesc);
}