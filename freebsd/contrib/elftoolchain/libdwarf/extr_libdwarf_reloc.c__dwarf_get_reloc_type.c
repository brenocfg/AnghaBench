#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int dbgp_isa; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_P_Debug ;

/* Variables and functions */
#define  DW_ISA_AARCH64 136 
#define  DW_ISA_ARM 135 
#define  DW_ISA_IA64 134 
#define  DW_ISA_MIPS 133 
#define  DW_ISA_PPC 132 
#define  DW_ISA_RISCV 131 
#define  DW_ISA_SPARC 130 
#define  DW_ISA_X86 129 
#define  DW_ISA_X86_64 128 
 int /*<<< orphan*/  R_386_32 ; 
 int /*<<< orphan*/  R_AARCH64_ABS32 ; 
 int /*<<< orphan*/  R_AARCH64_ABS64 ; 
 int /*<<< orphan*/  R_ARM_ABS32 ; 
 int /*<<< orphan*/  R_IA_64_DIR32LSB ; 
 int /*<<< orphan*/  R_IA_64_DIR64LSB ; 
 int /*<<< orphan*/  R_MIPS_32 ; 
 int /*<<< orphan*/  R_MIPS_64 ; 
 int /*<<< orphan*/  R_PPC64_ADDR64 ; 
 int /*<<< orphan*/  R_PPC_ADDR32 ; 
 int /*<<< orphan*/  R_RISCV_32 ; 
 int /*<<< orphan*/  R_RISCV_64 ; 
 int /*<<< orphan*/  R_SPARC_UA32 ; 
 int /*<<< orphan*/  R_SPARC_UA64 ; 
 int /*<<< orphan*/  R_X86_64_32 ; 
 int /*<<< orphan*/  R_X86_64_64 ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

Dwarf_Unsigned
_dwarf_get_reloc_type(Dwarf_P_Debug dbg, int is64)
{

	assert(dbg != NULL);

	switch (dbg->dbgp_isa) {
	case DW_ISA_AARCH64:
		return (is64 ? R_AARCH64_ABS64 : R_AARCH64_ABS32);
	case DW_ISA_X86:
		return (R_386_32);
	case DW_ISA_X86_64:
		return (is64 ? R_X86_64_64 : R_X86_64_32);
	case DW_ISA_SPARC:
		return (is64 ? R_SPARC_UA64 : R_SPARC_UA32);
	case DW_ISA_PPC:
		return (is64 ? R_PPC64_ADDR64 : R_PPC_ADDR32);
	case DW_ISA_ARM:
		return (R_ARM_ABS32);
	case DW_ISA_MIPS:
		return (is64 ? R_MIPS_64 : R_MIPS_32);
	case DW_ISA_RISCV:
		return (is64 ? R_RISCV_64 : R_RISCV_32);
	case DW_ISA_IA64:
		return (is64 ? R_IA_64_DIR64LSB : R_IA_64_DIR32LSB);
	default:
		break;
	}
	return (0);		/* NOT REACHED */
}