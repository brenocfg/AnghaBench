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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  enum insn_code { ____Placeholder_insn_code } insn_code ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,int) ;} ;
typedef  int /*<<< orphan*/  REAL_VALUE_TYPE ;

/* Variables and functions */
 int CODE_FOR_nothing ; 
 int /*<<< orphan*/  CONST_DOUBLE_FROM_REAL_VALUE (int /*<<< orphan*/ ,int) ; 
 int GET_CLASS_NARROWEST_MODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 scalar_t__ LEGITIMATE_CONSTANT_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  REAL_VALUE_FROM_CONST_DOUBLE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_EQUAL ; 
 scalar_t__ REG_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET ; 
 int /*<<< orphan*/  UNKNOWN ; 
 int can_extend_p (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_unop_insn (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exact_real_truncate (int,int /*<<< orphan*/ *) ; 
 scalar_t__** float_extend_from_mem ; 
 int /*<<< orphan*/  force_const_mem (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  force_reg (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_FLOAT_EXTEND (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_last_insn () ; 
 TYPE_2__* insn_data ; 
 int rtx_cost (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_unique_reg_note (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  validize_mem (int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
compress_float_constant (rtx x, rtx y)
{
  enum machine_mode dstmode = GET_MODE (x);
  enum machine_mode orig_srcmode = GET_MODE (y);
  enum machine_mode srcmode;
  REAL_VALUE_TYPE r;
  int oldcost, newcost;

  REAL_VALUE_FROM_CONST_DOUBLE (r, y);

  if (LEGITIMATE_CONSTANT_P (y))
    oldcost = rtx_cost (y, SET);
  else
    oldcost = rtx_cost (force_const_mem (dstmode, y), SET);

  for (srcmode = GET_CLASS_NARROWEST_MODE (GET_MODE_CLASS (orig_srcmode));
       srcmode != orig_srcmode;
       srcmode = GET_MODE_WIDER_MODE (srcmode))
    {
      enum insn_code ic;
      rtx trunc_y, last_insn;

      /* Skip if the target can't extend this way.  */
      ic = can_extend_p (dstmode, srcmode, 0);
      if (ic == CODE_FOR_nothing)
	continue;

      /* Skip if the narrowed value isn't exact.  */
      if (! exact_real_truncate (srcmode, &r))
	continue;

      trunc_y = CONST_DOUBLE_FROM_REAL_VALUE (r, srcmode);

      if (LEGITIMATE_CONSTANT_P (trunc_y))
	{
	  /* Skip if the target needs extra instructions to perform
	     the extension.  */
	  if (! (*insn_data[ic].operand[1].predicate) (trunc_y, srcmode))
	    continue;
	  /* This is valid, but may not be cheaper than the original. */
	  newcost = rtx_cost (gen_rtx_FLOAT_EXTEND (dstmode, trunc_y), SET);
	  if (oldcost < newcost)
	    continue;
	}
      else if (float_extend_from_mem[dstmode][srcmode])
	{
	  trunc_y = force_const_mem (srcmode, trunc_y);
	  /* This is valid, but may not be cheaper than the original. */
	  newcost = rtx_cost (gen_rtx_FLOAT_EXTEND (dstmode, trunc_y), SET);
	  if (oldcost < newcost)
	    continue;
	  trunc_y = validize_mem (trunc_y);
	}
      else
	continue;

      /* For CSE's benefit, force the compressed constant pool entry
	 into a new pseudo.  This constant may be used in different modes,
	 and if not, combine will put things back together for us.  */
      trunc_y = force_reg (srcmode, trunc_y);
      emit_unop_insn (ic, x, trunc_y, UNKNOWN);
      last_insn = get_last_insn ();

      if (REG_P (x))
	set_unique_reg_note (last_insn, REG_EQUAL, y);

      return last_insn;
    }

  return NULL_RTX;
}