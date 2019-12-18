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
struct disassemble_info {int /*<<< orphan*/  bytes_per_line; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  SLOT_MULTIPLIER ; 
 int print_insn_ia64 (int /*<<< orphan*/ ,struct disassemble_info*) ; 

__attribute__((used)) static int
ia64_print_insn (bfd_vma memaddr, struct disassemble_info *info)
{
  info->bytes_per_line = SLOT_MULTIPLIER;
  return print_insn_ia64 (memaddr, info);
}