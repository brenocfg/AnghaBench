#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int X_add_number; } ;
struct TYPE_6__ {TYPE_1__ exp; } ;
struct TYPE_8__ {void* error; TYPE_3__* operands; TYPE_2__ reloc; } ;
struct TYPE_7__ {int reg; int imm; int shifted; } ;

/* Variables and functions */
 int FAIL ; 
 size_t REG_TYPE_RN ; 
 int /*<<< orphan*/  SHIFT_LSL_IMMEDIATE ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 int arm_reg_parse (char**,size_t) ; 
 TYPE_4__ inst ; 
 int parse_shift (char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** reg_expected_msgs ; 
 int skip_past_char (char**,char) ; 
 int skip_past_comma (char**) ; 

__attribute__((used)) static int
parse_tb (char **str)
{
  char * p = *str;
  int reg;

  if (skip_past_char (&p, '[') == FAIL)
    {
      inst.error = _("'[' expected");
      return FAIL;
    }

  if ((reg = arm_reg_parse (&p, REG_TYPE_RN)) == FAIL)
    {
      inst.error = _(reg_expected_msgs[REG_TYPE_RN]);
      return FAIL;
    }
  inst.operands[0].reg = reg;

  if (skip_past_comma (&p) == FAIL)
    {
      inst.error = _("',' expected");
      return FAIL;
    }
  
  if ((reg = arm_reg_parse (&p, REG_TYPE_RN)) == FAIL)
    {
      inst.error = _(reg_expected_msgs[REG_TYPE_RN]);
      return FAIL;
    }
  inst.operands[0].imm = reg;

  if (skip_past_comma (&p) == SUCCESS)
    {
      if (parse_shift (&p, 0, SHIFT_LSL_IMMEDIATE) == FAIL)
	return FAIL;
      if (inst.reloc.exp.X_add_number != 1)
	{
	  inst.error = _("invalid shift");
	  return FAIL;
	}
      inst.operands[0].shifted = 1;
    }

  if (skip_past_char (&p, ']') == FAIL)
    {
      inst.error = _("']' expected");
      return FAIL;
    }
  *str = p;
  return SUCCESS;
}