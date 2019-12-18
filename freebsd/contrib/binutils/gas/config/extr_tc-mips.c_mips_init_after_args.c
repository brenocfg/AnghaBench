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
struct mips_opcode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_mips_num_builtin_opcodes ; 
 int /*<<< orphan*/  bfd_mips_num_opcodes ; 
 scalar_t__ mips_builtin_opcodes ; 
 struct mips_opcode* mips_opcodes ; 

void
mips_init_after_args (void)
{
  /* initialize opcodes */
  bfd_mips_num_opcodes = bfd_mips_num_builtin_opcodes;
  mips_opcodes = (struct mips_opcode *) mips_builtin_opcodes;
}