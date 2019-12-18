#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_mode ;
struct TYPE_18__ {TYPE_1__* detail; } ;
typedef  TYPE_2__ cs_insn ;
typedef  int cs_arch ;
struct TYPE_17__ {int groups_count; int /*<<< orphan*/ * groups; } ;

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
 char* cs_group_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_insn_detail_arm (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_arm64 (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_evm (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_m680x (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_m68k (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_mips (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_mos65xx (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_ppc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_sparc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_sysz (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_tms320c64x (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_x86 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_insn_detail_xcore (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void print_details(csh handle, cs_arch arch, cs_mode md, cs_insn *ins)
{
	switch(arch) {
		case CS_ARCH_X86:
			print_insn_detail_x86(handle, md, ins);
			break;
		case CS_ARCH_ARM:
			print_insn_detail_arm(handle, ins);
			break;
		case CS_ARCH_ARM64:
			print_insn_detail_arm64(handle, ins);
			break;
		case CS_ARCH_MIPS:
			print_insn_detail_mips(handle, ins);
			break;
		case CS_ARCH_PPC:
			print_insn_detail_ppc(handle, ins);
			break;
		case CS_ARCH_SPARC:
			print_insn_detail_sparc(handle, ins);
			break;
		case CS_ARCH_SYSZ:
			print_insn_detail_sysz(handle, ins);
			break;
		case CS_ARCH_XCORE:
			print_insn_detail_xcore(handle, ins);
			break;
		case CS_ARCH_M68K:
			print_insn_detail_m68k(handle, ins);
			break;
		case CS_ARCH_TMS320C64X:
			print_insn_detail_tms320c64x(handle, ins);
			break;
		case CS_ARCH_M680X:
			print_insn_detail_m680x(handle, ins);
			break;
		case CS_ARCH_EVM:
			print_insn_detail_evm(handle, ins);
			break;
		case CS_ARCH_MOS65XX:
			print_insn_detail_mos65xx(handle, ins);
			break;
		default: break;
	}

	if (ins->detail->groups_count) {
		int j;

		printf("\tGroups: ");
		for(j = 0; j < ins->detail->groups_count; j++) {
			printf("%s ", cs_group_name(handle, ins->detail->groups[j]));
		}
		printf("\n");
	}

	printf("\n");
}