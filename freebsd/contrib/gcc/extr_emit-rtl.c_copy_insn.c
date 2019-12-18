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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 scalar_t__ copy_asm_constraints_vector ; 
 scalar_t__ copy_asm_operands_vector ; 
 int /*<<< orphan*/  copy_insn_1 (int /*<<< orphan*/ ) ; 
 scalar_t__ copy_insn_n_scratches ; 
 scalar_t__ orig_asm_constraints_vector ; 
 scalar_t__ orig_asm_operands_vector ; 

rtx
copy_insn (rtx insn)
{
  copy_insn_n_scratches = 0;
  orig_asm_operands_vector = 0;
  orig_asm_constraints_vector = 0;
  copy_asm_operands_vector = 0;
  copy_asm_constraints_vector = 0;
  return copy_insn_1 (insn);
}