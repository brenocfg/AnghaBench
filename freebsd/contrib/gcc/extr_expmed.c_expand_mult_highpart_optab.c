#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ rtx ;
typedef  TYPE_2__* optab ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_10__ {TYPE_1__* handlers; } ;
struct TYPE_9__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 int BITS_PER_WORD ; 
 scalar_t__ CODE_FOR_nothing ; 
 int GET_MODE_BITSIZE (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  INTVAL (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int /*<<< orphan*/  SCALAR_FLOAT_MODE_P (int) ; 
 int* add_cost ; 
 scalar_t__ convert_modes (int,int,scalar_t__,int) ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  end_sequence () ; 
 scalar_t__ expand_binop (int,TYPE_2__*,scalar_t__,scalar_t__,scalar_t__,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_mult_highpart_adjust (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ extract_high_half (int,scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_int_mode (int /*<<< orphan*/ ,int) ; 
 scalar_t__ get_insns () ; 
 int* mul_cost ; 
 int* mul_highpart_cost ; 
 int* mul_widen_cost ; 
 int** shift_cost ; 
 TYPE_2__* smul_highpart_optab ; 
 TYPE_2__* smul_optab ; 
 TYPE_2__* smul_widen_optab ; 
 int /*<<< orphan*/  start_sequence () ; 
 TYPE_2__* umul_highpart_optab ; 
 TYPE_2__* umul_widen_optab ; 

__attribute__((used)) static rtx
expand_mult_highpart_optab (enum machine_mode mode, rtx op0, rtx op1,
			    rtx target, int unsignedp, int max_cost)
{
  rtx narrow_op1 = gen_int_mode (INTVAL (op1), mode);
  enum machine_mode wider_mode;
  optab moptab;
  rtx tem;
  int size;

  gcc_assert (!SCALAR_FLOAT_MODE_P (mode));

  wider_mode = GET_MODE_WIDER_MODE (mode);
  size = GET_MODE_BITSIZE (mode);

  /* Firstly, try using a multiplication insn that only generates the needed
     high part of the product, and in the sign flavor of unsignedp.  */
  if (mul_highpart_cost[mode] < max_cost)
    {
      moptab = unsignedp ? umul_highpart_optab : smul_highpart_optab;
      tem = expand_binop (mode, moptab, op0, narrow_op1, target,
			  unsignedp, OPTAB_DIRECT);
      if (tem)
	return tem;
    }

  /* Secondly, same as above, but use sign flavor opposite of unsignedp.
     Need to adjust the result after the multiplication.  */
  if (size - 1 < BITS_PER_WORD
      && (mul_highpart_cost[mode] + 2 * shift_cost[mode][size-1]
	  + 4 * add_cost[mode] < max_cost))
    {
      moptab = unsignedp ? smul_highpart_optab : umul_highpart_optab;
      tem = expand_binop (mode, moptab, op0, narrow_op1, target,
			  unsignedp, OPTAB_DIRECT);
      if (tem)
	/* We used the wrong signedness.  Adjust the result.  */
	return expand_mult_highpart_adjust (mode, tem, op0, narrow_op1,
					    tem, unsignedp);
    }

  /* Try widening multiplication.  */
  moptab = unsignedp ? umul_widen_optab : smul_widen_optab;
  if (moptab->handlers[wider_mode].insn_code != CODE_FOR_nothing
      && mul_widen_cost[wider_mode] < max_cost)
    {
      tem = expand_binop (wider_mode, moptab, op0, narrow_op1, 0,
			  unsignedp, OPTAB_WIDEN);
      if (tem)
	return extract_high_half (mode, tem);
    }

  /* Try widening the mode and perform a non-widening multiplication.  */
  if (smul_optab->handlers[wider_mode].insn_code != CODE_FOR_nothing
      && size - 1 < BITS_PER_WORD
      && mul_cost[wider_mode] + shift_cost[mode][size-1] < max_cost)
    {
      rtx insns, wop0, wop1;

      /* We need to widen the operands, for example to ensure the
	 constant multiplier is correctly sign or zero extended.
	 Use a sequence to clean-up any instructions emitted by
	 the conversions if things don't work out.  */
      start_sequence ();
      wop0 = convert_modes (wider_mode, mode, op0, unsignedp);
      wop1 = convert_modes (wider_mode, mode, op1, unsignedp);
      tem = expand_binop (wider_mode, smul_optab, wop0, wop1, 0,
			  unsignedp, OPTAB_WIDEN);
      insns = get_insns ();
      end_sequence ();

      if (tem)
	{
	  emit_insn (insns);
	  return extract_high_half (mode, tem);
	}
    }

  /* Try widening multiplication of opposite signedness, and adjust.  */
  moptab = unsignedp ? smul_widen_optab : umul_widen_optab;
  if (moptab->handlers[wider_mode].insn_code != CODE_FOR_nothing
      && size - 1 < BITS_PER_WORD
      && (mul_widen_cost[wider_mode] + 2 * shift_cost[mode][size-1]
	  + 4 * add_cost[mode] < max_cost))
    {
      tem = expand_binop (wider_mode, moptab, op0, narrow_op1,
			  NULL_RTX, ! unsignedp, OPTAB_WIDEN);
      if (tem != 0)
	{
	  tem = extract_high_half (mode, tem);
	  /* We used the wrong signedness.  Adjust the result.  */
	  return expand_mult_highpart_adjust (mode, tem, op0, narrow_op1,
					      target, unsignedp);
	}
    }

  return 0;
}