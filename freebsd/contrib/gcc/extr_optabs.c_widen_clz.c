#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  enum mode_class { ____Placeholder_mode_class } mode_class ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_5__ {TYPE_1__* handlers; } ;
struct TYPE_4__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 scalar_t__ CLASS_HAS_WIDER_MODES_P (int) ; 
 scalar_t__ CODE_FOR_nothing ; 
 int /*<<< orphan*/  GEN_INT (scalar_t__) ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 int GET_MODE_CLASS (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int VOIDmode ; 
 TYPE_2__* clz_optab ; 
 int /*<<< orphan*/  delete_insns_since (scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_unop (int,TYPE_2__*,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ gen_reg_rtx (int) ; 
 scalar_t__ get_last_insn () ; 
 int /*<<< orphan*/  sub_optab ; 
 scalar_t__ widen_operand (scalar_t__,int,int,int,int) ; 

__attribute__((used)) static rtx
widen_clz (enum machine_mode mode, rtx op0, rtx target)
{
  enum mode_class class = GET_MODE_CLASS (mode);
  if (CLASS_HAS_WIDER_MODES_P (class))
    {
      enum machine_mode wider_mode;
      for (wider_mode = GET_MODE_WIDER_MODE (mode);
	   wider_mode != VOIDmode;
	   wider_mode = GET_MODE_WIDER_MODE (wider_mode))
	{
	  if (clz_optab->handlers[(int) wider_mode].insn_code
	      != CODE_FOR_nothing)
	    {
	      rtx xop0, temp, last;

	      last = get_last_insn ();

	      if (target == 0)
		target = gen_reg_rtx (mode);
	      xop0 = widen_operand (op0, wider_mode, mode, true, false);
	      temp = expand_unop (wider_mode, clz_optab, xop0, NULL_RTX, true);
	      if (temp != 0)
		temp = expand_binop (wider_mode, sub_optab, temp,
				     GEN_INT (GET_MODE_BITSIZE (wider_mode)
					      - GET_MODE_BITSIZE (mode)),
				     target, true, OPTAB_DIRECT);
	      if (temp == 0)
		delete_insns_since (last);

	      return temp;
	    }
	}
    }
  return 0;
}