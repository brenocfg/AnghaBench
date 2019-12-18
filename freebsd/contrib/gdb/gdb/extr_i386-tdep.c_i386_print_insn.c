#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct disassemble_info {char* disassembler_options; int /*<<< orphan*/  mach; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
struct TYPE_2__ {int /*<<< orphan*/  mach; } ;

/* Variables and functions */
 scalar_t__ att_flavor ; 
 int /*<<< orphan*/  current_gdbarch ; 
 scalar_t__ disassembly_flavor ; 
 int /*<<< orphan*/  gdb_assert (int) ; 
 TYPE_1__* gdbarch_bfd_arch_info (int /*<<< orphan*/ ) ; 
 scalar_t__ intel_flavor ; 
 int print_insn_i386 (int /*<<< orphan*/ ,struct disassemble_info*) ; 

__attribute__((used)) static int
i386_print_insn (bfd_vma pc, struct disassemble_info *info)
{
  gdb_assert (disassembly_flavor == att_flavor
	      || disassembly_flavor == intel_flavor);

  /* FIXME: kettenis/20020915: Until disassembler_options is properly
     constified, cast to prevent a compiler warning.  */
  info->disassembler_options = (char *) disassembly_flavor;
  info->mach = gdbarch_bfd_arch_info (current_gdbarch)->mach;

  return print_insn_i386 (pc, info);
}