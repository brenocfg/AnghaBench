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
struct real_format {scalar_t__ signbit_ro; scalar_t__ signbit_rw; int /*<<< orphan*/  has_signed_zero; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {TYPE_2__* handlers; } ;
struct TYPE_7__ {TYPE_1__* handlers; } ;
struct TYPE_6__ {scalar_t__ insn_code; } ;
struct TYPE_5__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABS ; 
 scalar_t__ CODE_FOR_nothing ; 
 scalar_t__ CONST_DOUBLE ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (scalar_t__) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_DIRECT ; 
 struct real_format* REAL_MODE_FORMAT (int) ; 
 int SCALAR_FLOAT_MODE_P (int) ; 
 TYPE_4__* abs_optab ; 
 int /*<<< orphan*/  copysign_optab ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_copysign_absneg (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 scalar_t__ expand_copysign_bit (int,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 TYPE_3__* neg_optab ; 
 scalar_t__ real_isneg (int /*<<< orphan*/ ) ; 
 scalar_t__ simplify_unary_operation (int /*<<< orphan*/ ,int,scalar_t__,int) ; 

rtx
expand_copysign (rtx op0, rtx op1, rtx target)
{
  enum machine_mode mode = GET_MODE (op0);
  const struct real_format *fmt;
  bool op0_is_abs;
  rtx temp;

  gcc_assert (SCALAR_FLOAT_MODE_P (mode));
  gcc_assert (GET_MODE (op1) == mode);

  /* First try to do it with a special instruction.  */
  temp = expand_binop (mode, copysign_optab, op0, op1,
		       target, 0, OPTAB_DIRECT);
  if (temp)
    return temp;

  fmt = REAL_MODE_FORMAT (mode);
  if (fmt == NULL || !fmt->has_signed_zero)
    return NULL_RTX;

  op0_is_abs = false;
  if (GET_CODE (op0) == CONST_DOUBLE)
    {
      if (real_isneg (CONST_DOUBLE_REAL_VALUE (op0)))
	op0 = simplify_unary_operation (ABS, mode, op0, mode);
      op0_is_abs = true;
    }

  if (fmt->signbit_ro >= 0
      && (GET_CODE (op0) == CONST_DOUBLE
	  || (neg_optab->handlers[mode].insn_code != CODE_FOR_nothing
	      && abs_optab->handlers[mode].insn_code != CODE_FOR_nothing)))
    {
      temp = expand_copysign_absneg (mode, op0, op1, target,
				     fmt->signbit_ro, op0_is_abs);
      if (temp)
	return temp;
    }

  if (fmt->signbit_rw < 0)
    return NULL_RTX;
  return expand_copysign_bit (mode, op0, op1, target,
			      fmt->signbit_rw, op0_is_abs);
}