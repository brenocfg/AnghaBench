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
 int /*<<< orphan*/  CS_ARCH_ARM ; 
 int /*<<< orphan*/  CS_ARCH_ARM64 ; 
 int /*<<< orphan*/  CS_ARCH_EVM ; 
 int /*<<< orphan*/  CS_ARCH_M680X ; 
 int /*<<< orphan*/  CS_ARCH_M68K ; 
 int /*<<< orphan*/  CS_ARCH_MIPS ; 
 int /*<<< orphan*/  CS_ARCH_MOS65XX ; 
 int /*<<< orphan*/  CS_ARCH_PPC ; 
 int /*<<< orphan*/  CS_ARCH_SPARC ; 
 int /*<<< orphan*/  CS_ARCH_SYSZ ; 
 int /*<<< orphan*/  CS_ARCH_TMS320C64X ; 
 int /*<<< orphan*/  CS_ARCH_X86 ; 
 int /*<<< orphan*/  CS_ARCH_XCORE ; 
 int CS_VERSION_EXTRA ; 
 int CS_VERSION_MAJOR ; 
 int CS_VERSION_MINOR ; 
 scalar_t__ cs_support (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void usage(char *prog)
{
	printf("Cstool for Capstone Disassembler Engine v%u.%u.%u\n\n", CS_VERSION_MAJOR, CS_VERSION_MINOR, CS_VERSION_EXTRA);
	printf("Syntax: %s [-u|-d|-s|-v] <arch+mode> <assembly-hexstring> [start-address-in-hex-format]\n", prog);
	printf("\nThe following <arch+mode> options are supported:\n");

	if (cs_support(CS_ARCH_X86)) {
		printf("        x16         16-bit mode (X86)\n");
		printf("        x32         32-bit mode (X86)\n");
		printf("        x64         64-bit mode (X86)\n");
		printf("        x16att      16-bit mode (X86), syntax AT&T\n");
		printf("        x32att      32-bit mode (X86), syntax AT&T\n");
		printf("        x64att      64-bit mode (X86), syntax AT&T\n");
	}

	if (cs_support(CS_ARCH_ARM)) {
		printf("        arm         arm\n");
		printf("        armbe       arm + big endian\n");
		printf("        thumb       thumb mode\n");
		printf("        thumbbe     thumb + big endian\n");
		printf("        cortexm     thumb + cortex-m extensions\n");
	}

	if (cs_support(CS_ARCH_ARM64)) {
		printf("        arm64       aarch64 mode\n");
		printf("        arm64be     aarch64 + big endian\n");
	}

	if (cs_support(CS_ARCH_MIPS)) {
		printf("        mips        mips32 + little endian\n");
		printf("        mipsbe      mips32 + big endian\n");
		printf("        mips64      mips64 + little endian\n");
		printf("        mips64be    mips64 + big endian\n");
	}

	if (cs_support(CS_ARCH_PPC)) {
		printf("        ppc64       ppc64 + little endian\n");
		printf("        ppc64be     ppc64 + big endian\n");
	}

	if (cs_support(CS_ARCH_SPARC)) {
		printf("        sparc       sparc\n");
	}

	if (cs_support(CS_ARCH_SYSZ)) {
		printf("        systemz     systemz (s390x)\n");
	}

	if (cs_support(CS_ARCH_XCORE)) {
		printf("        xcore       xcore\n");
	}

	if (cs_support(CS_ARCH_M68K)) {
		printf("        m68k        m68k + big endian\n");
		printf("        m68k40      m68k_040\n");
	}

	if (cs_support(CS_ARCH_TMS320C64X)) {
		printf("        tms320c64x  TMS320C64x\n");
	}

	if (cs_support(CS_ARCH_M680X)) {
		printf("        m6800       M6800/2\n");
		printf("        m6801       M6801/3\n");
		printf("        m6805       M6805\n");
		printf("        m6808       M68HC08\n");
		printf("        m6809       M6809\n");
		printf("        m6811       M68HC11\n");
		printf("        cpu12       M68HC12/HCS12\n");
		printf("        hd6301      HD6301/3\n");
		printf("        hd6309      HD6309\n");
		printf("        hcs08       HCS08\n");
	}

	if (cs_support(CS_ARCH_EVM)) {
		printf("        evm         Ethereum Virtual Machine\n");
	}

	if (cs_support(CS_ARCH_MOS65XX)) {
		printf("        mos65xx     MOS65XX family\n");
	}

	printf("\nExtra options:\n");
	printf("        -d show detailed information of the instructions\n");
	printf("        -u show immediates as unsigned\n");
	printf("        -s decode in SKIPDATA mode\n");
	printf("        -v show version & Capstone core build info\n\n");
}