#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct mips_arch_choice {int /*<<< orphan*/  hwr_names; scalar_t__ cp0sel_names_len; int /*<<< orphan*/ * cp0sel_names; int /*<<< orphan*/  cp0_names; int /*<<< orphan*/  isa; int /*<<< orphan*/  processor; } ;
struct disassemble_info {scalar_t__ flavour; int /*<<< orphan*/  mach; TYPE_1__* section; } ;
struct TYPE_4__ {int /*<<< orphan*/  isa; int /*<<< orphan*/  processor; } ;
struct TYPE_3__ {int /*<<< orphan*/  owner; } ;
typedef  int /*<<< orphan*/  Elf_Internal_Ehdr ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_R3000 ; 
 int /*<<< orphan*/  ISA_MIPS3 ; 
 scalar_t__ bfd_target_elf_flavour ; 
 struct mips_arch_choice* choose_arch_by_number (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * elf_elfheader (int /*<<< orphan*/ ) ; 
 scalar_t__ is_newabi (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mips_cp0_names ; 
 int /*<<< orphan*/  mips_cp0_names_numeric ; 
 int /*<<< orphan*/ * mips_cp0sel_names ; 
 scalar_t__ mips_cp0sel_names_len ; 
 int /*<<< orphan*/  mips_fpr_names ; 
 int /*<<< orphan*/  mips_fpr_names_numeric ; 
 int /*<<< orphan*/  mips_gpr_names ; 
 int /*<<< orphan*/  mips_gpr_names_newabi ; 
 int /*<<< orphan*/  mips_gpr_names_oldabi ; 
 int /*<<< orphan*/  mips_hwr_names ; 
 int /*<<< orphan*/  mips_hwr_names_numeric ; 
 int /*<<< orphan*/  mips_isa ; 
 int /*<<< orphan*/  mips_processor ; 
 TYPE_2__ mips_target_info ; 
 scalar_t__ no_aliases ; 
 int /*<<< orphan*/  target_processor ; 

__attribute__((used)) static void
set_default_mips_dis_options (struct disassemble_info *info)
{
  const struct mips_arch_choice *chosen_arch;

  /* Defaults: mipsIII/r3000 (?!), (o)32-style ("oldabi") GPR names,
     and numeric FPR, CP0 register, and HWR names.  */
  mips_isa = ISA_MIPS3;
  mips_processor =  CPU_R3000;
  mips_gpr_names = mips_gpr_names_oldabi;
  mips_fpr_names = mips_fpr_names_numeric;
  mips_cp0_names = mips_cp0_names_numeric;
  mips_cp0sel_names = NULL;
  mips_cp0sel_names_len = 0;
  mips_hwr_names = mips_hwr_names_numeric;
  no_aliases = 0;

  /* If an ELF "newabi" binary, use the n32/(n)64 GPR names.  */
  if (info->flavour == bfd_target_elf_flavour && info->section != NULL)
    {
      Elf_Internal_Ehdr *header;

      header = elf_elfheader (info->section->owner);
      if (is_newabi (header))
	mips_gpr_names = mips_gpr_names_newabi;
    }

  /* Set ISA, architecture, and cp0 register names as best we can.  */
#if ! SYMTAB_AVAILABLE
  /* This is running out on a target machine, not in a host tool.
     FIXME: Where does mips_target_info come from?  */
  target_processor = mips_target_info.processor;
  mips_isa = mips_target_info.isa;
#else
  chosen_arch = choose_arch_by_number (info->mach);
  if (chosen_arch != NULL)
    {
      mips_processor = chosen_arch->processor;
      mips_isa = chosen_arch->isa;
      mips_cp0_names = chosen_arch->cp0_names;
      mips_cp0sel_names = chosen_arch->cp0sel_names;
      mips_cp0sel_names_len = chosen_arch->cp0sel_names_len;
      mips_hwr_names = chosen_arch->hwr_names;
    }
#endif
}