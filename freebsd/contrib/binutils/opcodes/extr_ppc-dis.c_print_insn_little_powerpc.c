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
struct disassemble_info {scalar_t__ private_data; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int print_insn_powerpc (int /*<<< orphan*/ ,struct disassemble_info*,int /*<<< orphan*/ ,int) ; 

int
print_insn_little_powerpc (bfd_vma memaddr, struct disassemble_info *info)
{
  int dialect = (char *) info->private_data - (char *) 0;
  return print_insn_powerpc (memaddr, info, 0, dialect);
}