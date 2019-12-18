#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct asm_shift_name {int kind; } ;
typedef  enum shift_kind { ____Placeholder_shift_kind } shift_kind ;
typedef  enum parse_shift_mode { ____Placeholder_parse_shift_mode } parse_shift_mode ;
struct TYPE_4__ {int /*<<< orphan*/  exp; } ;
struct TYPE_6__ {TYPE_2__* operands; TYPE_1__ reloc; void* error; } ;
struct TYPE_5__ {int imm; int immisreg; int shift_kind; int shifted; } ;

/* Variables and functions */
 int FAIL ; 
 int /*<<< orphan*/  GE_IMM_PREFIX ; 
 scalar_t__ ISALPHA (char) ; 
#define  NO_SHIFT_RESTRICT 132 
 int /*<<< orphan*/  REG_TYPE_RN ; 
 int SHIFT_ASR ; 
#define  SHIFT_ASR_IMMEDIATE 131 
#define  SHIFT_IMMEDIATE 130 
 int SHIFT_LSL ; 
#define  SHIFT_LSL_IMMEDIATE 129 
#define  SHIFT_LSL_OR_ASR_IMMEDIATE 128 
 int SHIFT_RRX ; 
 int SUCCESS ; 
 void* _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int arm_reg_parse (char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  arm_shift_hsh ; 
 struct asm_shift_name* hash_find_n (int /*<<< orphan*/ ,char*,int) ; 
 TYPE_3__ inst ; 
 scalar_t__ my_get_expression (int /*<<< orphan*/ *,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skip_whitespace (char*) ; 

__attribute__((used)) static int
parse_shift (char **str, int i, enum parse_shift_mode mode)
{
  const struct asm_shift_name *shift_name;
  enum shift_kind shift;
  char *s = *str;
  char *p = s;
  int reg;

  for (p = *str; ISALPHA (*p); p++)
    ;

  if (p == *str)
    {
      inst.error = _("shift expression expected");
      return FAIL;
    }

  shift_name = hash_find_n (arm_shift_hsh, *str, p - *str);

  if (shift_name == NULL)
    {
      inst.error = _("shift expression expected");
      return FAIL;
    }

  shift = shift_name->kind;

  switch (mode)
    {
    case NO_SHIFT_RESTRICT:
    case SHIFT_IMMEDIATE:   break;

    case SHIFT_LSL_OR_ASR_IMMEDIATE:
      if (shift != SHIFT_LSL && shift != SHIFT_ASR)
	{
	  inst.error = _("'LSL' or 'ASR' required");
	  return FAIL;
	}
      break;

    case SHIFT_LSL_IMMEDIATE:
      if (shift != SHIFT_LSL)
	{
	  inst.error = _("'LSL' required");
	  return FAIL;
	}
      break;

    case SHIFT_ASR_IMMEDIATE:
      if (shift != SHIFT_ASR)
	{
	  inst.error = _("'ASR' required");
	  return FAIL;
	}
      break;

    default: abort ();
    }

  if (shift != SHIFT_RRX)
    {
      /* Whitespace can appear here if the next thing is a bare digit.	*/
      skip_whitespace (p);

      if (mode == NO_SHIFT_RESTRICT
	  && (reg = arm_reg_parse (&p, REG_TYPE_RN)) != FAIL)
	{
	  inst.operands[i].imm = reg;
	  inst.operands[i].immisreg = 1;
	}
      else if (my_get_expression (&inst.reloc.exp, &p, GE_IMM_PREFIX))
	return FAIL;
    }
  inst.operands[i].shift_kind = shift;
  inst.operands[i].shifted = 1;
  *str = p;
  return SUCCESS;
}