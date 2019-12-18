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
struct disassemble_info {int arch; int skip_zeroes; int /*<<< orphan*/  insn_sets; int /*<<< orphan*/  mach; int /*<<< orphan*/  endian; int /*<<< orphan*/  skip_zeroes_at_end; int /*<<< orphan*/  disassembler_needs_relocs; int /*<<< orphan*/  symbol_is_valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ENDIAN_BIG ; 
 int /*<<< orphan*/  ISA_M16C ; 
 int /*<<< orphan*/  ISA_M32C ; 
 int /*<<< orphan*/  ISA_MAX ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  arm_symbol_is_valid ; 
#define  bfd_arch_arm 132 
#define  bfd_arch_ia64 131 
#define  bfd_arch_m32c 130 
#define  bfd_arch_mep 129 
#define  bfd_arch_tic4x 128 
 int /*<<< orphan*/  bfd_mach_m16c ; 
 int /*<<< orphan*/  cgen_bitset_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgen_bitset_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
disassemble_init_for_target (struct disassemble_info * info)
{
  if (info == NULL)
    return;

  switch (info->arch)
    {
#ifdef ARCH_arm
    case bfd_arch_arm:
      info->symbol_is_valid = arm_symbol_is_valid;
      info->disassembler_needs_relocs = TRUE;
      break;
#endif
#ifdef ARCH_ia64
    case bfd_arch_ia64:
      info->skip_zeroes = 16;
      break;
#endif
#ifdef ARCH_tic4x
    case bfd_arch_tic4x:
      info->skip_zeroes = 32;
      break;
#endif
#ifdef ARCH_mep
    case bfd_arch_mep:
      info->skip_zeroes = 256;
      info->skip_zeroes_at_end = 0;
      break;
#endif
#ifdef ARCH_m32c
    case bfd_arch_m32c:
      info->endian = BFD_ENDIAN_BIG;
      if (! info->insn_sets)
	{
	  info->insn_sets = cgen_bitset_create (ISA_MAX);
	  if (info->mach == bfd_mach_m16c)
	    cgen_bitset_set (info->insn_sets, ISA_M16C);
	  else
	    cgen_bitset_set (info->insn_sets, ISA_M32C);
	}
      break;
#endif
    default:
      break;
    }
}