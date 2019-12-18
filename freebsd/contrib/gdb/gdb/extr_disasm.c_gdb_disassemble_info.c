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
struct ui_file {int dummy; } ;
struct gdbarch {int dummy; } ;
struct disassemble_info {int /*<<< orphan*/  endian; int /*<<< orphan*/  mach; int /*<<< orphan*/  arch; int /*<<< orphan*/  read_memory_func; int /*<<< orphan*/  print_address_func; int /*<<< orphan*/  memory_error_func; int /*<<< orphan*/  flavour; } ;
struct TYPE_2__ {int /*<<< orphan*/  mach; int /*<<< orphan*/  arch; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_target_unknown_flavour ; 
 int /*<<< orphan*/  dis_asm_memory_error ; 
 int /*<<< orphan*/  dis_asm_print_address ; 
 int /*<<< orphan*/  dis_asm_read_memory ; 
 int /*<<< orphan*/  fprintf_disasm ; 
 TYPE_1__* gdbarch_bfd_arch_info (struct gdbarch*) ; 
 int /*<<< orphan*/  gdbarch_byte_order (struct gdbarch*) ; 
 int /*<<< orphan*/  init_disassemble_info (struct disassemble_info*,struct ui_file*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct disassemble_info
gdb_disassemble_info (struct gdbarch *gdbarch, struct ui_file *file)
{
  struct disassemble_info di;
  init_disassemble_info (&di, file, fprintf_disasm);
  di.flavour = bfd_target_unknown_flavour;
  di.memory_error_func = dis_asm_memory_error;
  di.print_address_func = dis_asm_print_address;
  /* NOTE: cagney/2003-04-28: The original code, from the old Insight
     disassembler had a local optomization here.  By default it would
     access the executable file, instead of the target memory (there
     was a growing list of exceptions though).  Unfortunately, the
     heuristic was flawed.  Commands like "disassemble &variable"
     didn't work as they relied on the access going to the target.
     Further, it has been supperseeded by trust-read-only-sections
     (although that should be superseeded by target_trust..._p()).  */
  di.read_memory_func = dis_asm_read_memory;
  di.arch = gdbarch_bfd_arch_info (gdbarch)->arch;
  di.mach = gdbarch_bfd_arch_info (gdbarch)->mach;
  di.endian = gdbarch_byte_order (gdbarch);
  return di;
}