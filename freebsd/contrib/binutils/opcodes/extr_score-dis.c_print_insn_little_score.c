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
struct disassemble_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int print_insn (int /*<<< orphan*/ ,struct disassemble_info*,int /*<<< orphan*/ ) ; 

int
print_insn_little_score (bfd_vma pc, struct disassemble_info *info)
{
  return print_insn (pc, info, TRUE);
}