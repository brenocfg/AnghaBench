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
typedef  enum reg_class { ____Placeholder_reg_class } reg_class ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_4__ {int n_operands; TYPE_1__* operand; } ;
struct TYPE_3__ {char* constraint; } ;

/* Variables and functions */
 int GENERAL_REGS ; 
 int NO_REGS ; 
 int REG_CLASS_FROM_CONSTRAINT (unsigned char,char const*) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_2__* insn_data ; 

enum reg_class
scratch_reload_class (enum insn_code icode)
{
  const char *scratch_constraint;
  char scratch_letter;
  enum reg_class class;

  gcc_assert (insn_data[(int) icode].n_operands == 3);
  scratch_constraint = insn_data[(int) icode].operand[2].constraint;
  gcc_assert (*scratch_constraint == '=');
  scratch_constraint++;
  if (*scratch_constraint == '&')
    scratch_constraint++;
  scratch_letter = *scratch_constraint;
  if (scratch_letter == 'r')
    return GENERAL_REGS;
  class = REG_CLASS_FROM_CONSTRAINT ((unsigned char) scratch_letter,
				     scratch_constraint);
  gcc_assert (class != NO_REGS);
  return class;
}