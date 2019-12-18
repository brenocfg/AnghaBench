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
struct TYPE_3__ {int dbg_machine; } ;
typedef  int /*<<< orphan*/  Dwarf_Unsigned ;
typedef  TYPE_1__* Dwarf_Debug ;

/* Variables and functions */
#define  EM_386 139 
#define  EM_AARCH64 138 
#define  EM_ARM 137 
#define  EM_IAMCU 136 
#define  EM_IA_64 135 
#define  EM_MIPS 134 
#define  EM_NONE 133 
#define  EM_PPC 132 
#define  EM_PPC64 131 
#define  EM_RISCV 130 
#define  EM_SPARC 129 
#define  EM_X86_64 128 
 int /*<<< orphan*/  R_386_32 ; 
 int /*<<< orphan*/  R_AARCH64_ABS32 ; 
 int /*<<< orphan*/  R_AARCH64_ABS64 ; 
 int /*<<< orphan*/  R_ARM_ABS32 ; 
 int /*<<< orphan*/  R_IA_64_DIR64LSB ; 
 int /*<<< orphan*/  R_IA_64_SECREL32LSB ; 
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

int
_dwarf_get_reloc_size(Dwarf_Debug dbg, Dwarf_Unsigned rel_type)
{

	switch (dbg->dbg_machine) {
	case EM_NONE:
		break;
	case EM_AARCH64:
		if (rel_type == R_AARCH64_ABS32)
			return (4);
		else if (rel_type == R_AARCH64_ABS64)
			return (8);
		break;
	case EM_ARM:
		if (rel_type == R_ARM_ABS32)
			return (4);
		break;
	case EM_386:
	case EM_IAMCU:
		if (rel_type == R_386_32)
			return (4);
		break;
	case EM_X86_64:
		if (rel_type == R_X86_64_32)
			return (4);
		else if (rel_type == R_X86_64_64)
			return (8);
		break;
	case EM_SPARC:
		if (rel_type == R_SPARC_UA32)
			return (4);
		else if (rel_type == R_SPARC_UA64)
			return (8);
		break;
	case EM_PPC:
		if (rel_type == R_PPC_ADDR32)
			return (4);
		break;
	case EM_PPC64:
		if (rel_type == R_PPC_ADDR32)
			return (4);
		else if (rel_type == R_PPC64_ADDR64)
			return (8);
		break;
	case EM_MIPS:
		if (rel_type == R_MIPS_32)
			return (4);
		else if (rel_type == R_MIPS_64)
			return (8);
		break;
	case EM_RISCV:
		if (rel_type == R_RISCV_32)
			return (4);
		else if (rel_type == R_RISCV_64)
			return (8);
		break;
	case EM_IA_64:
		if (rel_type == R_IA_64_SECREL32LSB)
			return (4);
		else if (rel_type == R_IA_64_DIR64LSB)
			return (8);
		break;
	default:
		break;
	}

	/* unknown relocation. */
	return (0);
}