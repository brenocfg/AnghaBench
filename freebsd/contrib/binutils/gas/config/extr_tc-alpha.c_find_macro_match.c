#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct alpha_macro {int* argsets; int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int X_op; int /*<<< orphan*/  X_add_number; } ;
typedef  TYPE_1__ expressionS ;
typedef  enum alpha_macro_arg { ____Placeholder_alpha_macro_arg } alpha_macro_arg ;

/* Variables and functions */
#define  MACRO_CPIR 148 
#define  MACRO_EOA 147 
#define  MACRO_EXP 146 
#define  MACRO_FPR 145 
#define  MACRO_IR 144 
#define  MACRO_OPIR 143 
#define  MACRO_PIR 142 
#define  O_absent 141 
#define  O_cpregister 140 
#define  O_gpdisp 139 
#define  O_gprel 138 
#define  O_gprelhigh 137 
#define  O_gprellow 136 
#define  O_illegal 135 
#define  O_literal 134 
#define  O_lituse_base 133 
#define  O_lituse_bytoff 132 
#define  O_lituse_jsr 131 
#define  O_pregister 130 
#define  O_register 129 
#define  O_samegp 128 
 struct alpha_macro const* alpha_macros ; 
 scalar_t__ alpha_num_macros ; 
 int /*<<< orphan*/  is_fpr_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_ir_num (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const struct alpha_macro *
find_macro_match (const struct alpha_macro *first_macro,
		  const expressionS *tok,
		  int *pntok)

{
  const struct alpha_macro *macro = first_macro;
  int ntok = *pntok;

  do
    {
      const enum alpha_macro_arg *arg = macro->argsets;
      int tokidx = 0;

      while (*arg)
	{
	  switch (*arg)
	    {
	    case MACRO_EOA:
	      if (tokidx == ntok)
		return macro;
	      else
		tokidx = 0;
	      break;

	      /* Index register.  */
	    case MACRO_IR:
	      if (tokidx >= ntok || tok[tokidx].X_op != O_register
		  || !is_ir_num (tok[tokidx].X_add_number))
		goto match_failed;
	      ++tokidx;
	      break;

	      /* Parenthesized index register.  */
	    case MACRO_PIR:
	      if (tokidx >= ntok || tok[tokidx].X_op != O_pregister
		  || !is_ir_num (tok[tokidx].X_add_number))
		goto match_failed;
	      ++tokidx;
	      break;

	      /* Optional parenthesized index register.  */
	    case MACRO_OPIR:
	      if (tokidx < ntok && tok[tokidx].X_op == O_pregister
		  && is_ir_num (tok[tokidx].X_add_number))
		++tokidx;
	      break;

	      /* Leading comma with a parenthesized index register.  */
	    case MACRO_CPIR:
	      if (tokidx >= ntok || tok[tokidx].X_op != O_cpregister
		  || !is_ir_num (tok[tokidx].X_add_number))
		goto match_failed;
	      ++tokidx;
	      break;

	      /* Floating point register.  */
	    case MACRO_FPR:
	      if (tokidx >= ntok || tok[tokidx].X_op != O_register
		  || !is_fpr_num (tok[tokidx].X_add_number))
		goto match_failed;
	      ++tokidx;
	      break;

	      /* Normal expression.  */
	    case MACRO_EXP:
	      if (tokidx >= ntok)
		goto match_failed;
	      switch (tok[tokidx].X_op)
		{
		case O_illegal:
		case O_absent:
		case O_register:
		case O_pregister:
		case O_cpregister:
		case O_literal:
		case O_lituse_base:
		case O_lituse_bytoff:
		case O_lituse_jsr:
		case O_gpdisp:
		case O_gprelhigh:
		case O_gprellow:
		case O_gprel:
		case O_samegp:
		  goto match_failed;

		default:
		  break;
		}
	      ++tokidx;
	      break;

	    match_failed:
	      while (*arg != MACRO_EOA)
		++arg;
	      tokidx = 0;
	      break;
	    }
	  ++arg;
	}
    }
  while (++macro - alpha_macros < (int) alpha_num_macros
	 && !strcmp (macro->name, first_macro->name));

  return NULL;
}