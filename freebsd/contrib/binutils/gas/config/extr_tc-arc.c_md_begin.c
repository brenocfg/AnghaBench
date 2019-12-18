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
 scalar_t__ BIG_ENDIAN ; 
 int /*<<< orphan*/  arc_get_opcode_mach (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  arc_mach_type ; 
 int /*<<< orphan*/  arc_opcode_init_tables (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_warn (char*) ; 
 int /*<<< orphan*/  bfd_arch_arc ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ byte_order ; 
 int /*<<< orphan*/  stdoutput ; 
 int target_big_endian ; 

void
md_begin (void)
{
  /* The endianness can be chosen "at the factory".  */
  target_big_endian = byte_order == BIG_ENDIAN;

  if (!bfd_set_arch_mach (stdoutput, bfd_arch_arc, arc_mach_type))
    as_warn ("could not set architecture and machine");

  /* This call is necessary because we need to initialize `arc_operand_map'
     which may be needed before we see the first insn.  */
  arc_opcode_init_tables (arc_get_opcode_mach (arc_mach_type,
					       target_big_endian));
}