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
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 scalar_t__ CONST0_RTX (int) ; 
 int /*<<< orphan*/  CONSTANT_P (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_INNER (int) ; 
 int GET_MODE_NUNITS (int) ; 
 int /*<<< orphan*/  XVEC (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_CONST_VECTOR (int,int /*<<< orphan*/ ) ; 
 scalar_t__ ix86_expand_vector_init_duplicate (int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ix86_expand_vector_init_general (int,int,scalar_t__,scalar_t__) ; 
 scalar_t__ ix86_expand_vector_init_one_nonzero (int,int,scalar_t__,scalar_t__,int) ; 
 scalar_t__ ix86_expand_vector_init_one_var (int,int,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 

void
ix86_expand_vector_init (bool mmx_ok, rtx target, rtx vals)
{
  enum machine_mode mode = GET_MODE (target);
  enum machine_mode inner_mode = GET_MODE_INNER (mode);
  int n_elts = GET_MODE_NUNITS (mode);
  int n_var = 0, one_var = -1;
  bool all_same = true, all_const_zero = true;
  int i;
  rtx x;

  for (i = 0; i < n_elts; ++i)
    {
      x = XVECEXP (vals, 0, i);
      if (!CONSTANT_P (x))
	n_var++, one_var = i;
      else if (x != CONST0_RTX (inner_mode))
	all_const_zero = false;
      if (i > 0 && !rtx_equal_p (x, XVECEXP (vals, 0, 0)))
	all_same = false;
    }

  /* Constants are best loaded from the constant pool.  */
  if (n_var == 0)
    {
      emit_move_insn (target, gen_rtx_CONST_VECTOR (mode, XVEC (vals, 0)));
      return;
    }

  /* If all values are identical, broadcast the value.  */
  if (all_same
      && ix86_expand_vector_init_duplicate (mmx_ok, mode, target,
					    XVECEXP (vals, 0, 0)))
    return;

  /* Values where only one field is non-constant are best loaded from
     the pool and overwritten via move later.  */
  if (n_var == 1)
    {
      if (all_const_zero
	  && ix86_expand_vector_init_one_nonzero (mmx_ok, mode, target,
						  XVECEXP (vals, 0, one_var),
						  one_var))
	return;

      if (ix86_expand_vector_init_one_var (mmx_ok, mode, target, vals, one_var))
	return;
    }

  ix86_expand_vector_init_general (mmx_ok, mode, target, vals);
}