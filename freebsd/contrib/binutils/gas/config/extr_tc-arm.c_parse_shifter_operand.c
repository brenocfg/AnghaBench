#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ X_op; int X_add_number; } ;
typedef  TYPE_3__ expressionS ;
struct TYPE_7__ {scalar_t__ pc_rel; int /*<<< orphan*/  type; TYPE_3__ exp; } ;
struct TYPE_9__ {TYPE_2__ reloc; void* error; TYPE_1__* operands; } ;
struct TYPE_6__ {int reg; int isreg; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_ARM_IMMEDIATE ; 
 int FAIL ; 
 int /*<<< orphan*/  GE_IMM_PREFIX ; 
 int /*<<< orphan*/  GE_NO_PREFIX ; 
 int /*<<< orphan*/  NO_SHIFT_RESTRICT ; 
 scalar_t__ O_constant ; 
 int /*<<< orphan*/  REG_TYPE_RN ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 int arm_reg_parse (char**,int /*<<< orphan*/ ) ; 
 TYPE_5__ inst ; 
 scalar_t__ my_get_expression (TYPE_3__*,char**,int /*<<< orphan*/ ) ; 
 int parse_shift (char**,int,int /*<<< orphan*/ ) ; 
 int skip_past_comma (char**) ; 

__attribute__((used)) static int
parse_shifter_operand (char **str, int i)
{
  int value;
  expressionS expr;

  if ((value = arm_reg_parse (str, REG_TYPE_RN)) != FAIL)
    {
      inst.operands[i].reg = value;
      inst.operands[i].isreg = 1;

      /* parse_shift will override this if appropriate */
      inst.reloc.exp.X_op = O_constant;
      inst.reloc.exp.X_add_number = 0;

      if (skip_past_comma (str) == FAIL)
	return SUCCESS;

      /* Shift operation on register.  */
      return parse_shift (str, i, NO_SHIFT_RESTRICT);
    }

  if (my_get_expression (&inst.reloc.exp, str, GE_IMM_PREFIX))
    return FAIL;

  if (skip_past_comma (str) == SUCCESS)
    {
      /* #x, y -- ie explicit rotation by Y.  */
      if (my_get_expression (&expr, str, GE_NO_PREFIX))
	return FAIL;

      if (expr.X_op != O_constant || inst.reloc.exp.X_op != O_constant)
	{
	  inst.error = _("constant expression expected");
	  return FAIL;
	}

      value = expr.X_add_number;
      if (value < 0 || value > 30 || value % 2 != 0)
	{
	  inst.error = _("invalid rotation");
	  return FAIL;
	}
      if (inst.reloc.exp.X_add_number < 0 || inst.reloc.exp.X_add_number > 255)
	{
	  inst.error = _("invalid constant");
	  return FAIL;
	}

      /* Convert to decoded value.  md_apply_fix will put it back.  */
      inst.reloc.exp.X_add_number
	= (((inst.reloc.exp.X_add_number << (32 - value))
	    | (inst.reloc.exp.X_add_number >> value)) & 0xffffffff);
    }

  inst.reloc.type = BFD_RELOC_ARM_IMMEDIATE;
  inst.reloc.pc_rel = 0;
  return SUCCESS;
}