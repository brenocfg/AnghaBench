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
#define  CS_ARCH_ARM 140 
#define  CS_ARCH_ARM64 139 
#define  CS_ARCH_EVM 138 
#define  CS_ARCH_M680X 137 
#define  CS_ARCH_M68K 136 
#define  CS_ARCH_MIPS 135 
#define  CS_ARCH_MOS65XX 134 
#define  CS_ARCH_PPC 133 
#define  CS_ARCH_SPARC 132 
#define  CS_ARCH_SYSZ 131 
#define  CS_ARCH_TMS320C64X 130 
#define  CS_ARCH_X86 129 
#define  CS_ARCH_XCORE 128 
 int /*<<< orphan*/  function ; 
 int /*<<< orphan*/  get_detail_arm ; 
 int /*<<< orphan*/  get_detail_arm64 ; 
 int /*<<< orphan*/  get_detail_evm ; 
 int /*<<< orphan*/  get_detail_m680x ; 
 int /*<<< orphan*/  get_detail_m68k ; 
 int /*<<< orphan*/  get_detail_mips ; 
 int /*<<< orphan*/  get_detail_mos65xx ; 
 int /*<<< orphan*/  get_detail_ppc ; 
 int /*<<< orphan*/  get_detail_sparc ; 
 int /*<<< orphan*/  get_detail_sysz ; 
 int /*<<< orphan*/  get_detail_tms320c64x ; 
 int /*<<< orphan*/  get_detail_x86 ; 
 int /*<<< orphan*/  get_detail_xcore ; 

int set_function(int arch)
{
	switch(arch) {
		case CS_ARCH_ARM:
			function = get_detail_arm;
			break;
		case CS_ARCH_ARM64:
			function = get_detail_arm64;
			break;
		case CS_ARCH_MIPS:
			function = get_detail_mips;
			break;
		case CS_ARCH_PPC:
			function = get_detail_ppc;
			break;
		case CS_ARCH_SPARC:
			function = get_detail_sparc;
			break;
		case CS_ARCH_SYSZ:
			function = get_detail_sysz;
			break;
		case CS_ARCH_X86:
			function = get_detail_x86;
			break;
		case CS_ARCH_XCORE:
			function = get_detail_xcore;
			break;
		case CS_ARCH_M68K:
			function = get_detail_m68k;
			break;
		case CS_ARCH_M680X:
			function = get_detail_m680x;
			break;
		case CS_ARCH_EVM:
			function = get_detail_evm;
			break;
		case CS_ARCH_MOS65XX:
			function = get_detail_mos65xx;
			break;
		case CS_ARCH_TMS320C64X:
			function = get_detail_tms320c64x;
			break;
		default:
			return -1;
	}
	return 0;
}