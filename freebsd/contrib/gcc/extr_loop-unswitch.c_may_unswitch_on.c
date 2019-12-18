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
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct rtx_iv {scalar_t__ step; scalar_t__ first_special; } ;
struct loop {int dummy; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  TYPE_1__* basic_block ;
struct TYPE_8__ {int /*<<< orphan*/  dest; } ;
struct TYPE_7__ {int /*<<< orphan*/  succs; } ;

/* Variables and functions */
 scalar_t__ BB_END (TYPE_1__*) ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 int EDGE_COUNT (int /*<<< orphan*/ ) ; 
 TYPE_4__* EDGE_SUCC (TYPE_1__*,int) ; 
 int /*<<< orphan*/  GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 scalar_t__ MODE_CC ; 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  SImode ; 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int /*<<< orphan*/  any_condjump_p (scalar_t__) ; 
 scalar_t__ canon_condition (int /*<<< orphan*/ ) ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const_true_rtx ; 
 int /*<<< orphan*/  flow_bb_inside_loop_p (struct loop*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_fmt_ee (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ get_condition (scalar_t__,scalar_t__*,int,int) ; 
 scalar_t__ get_iv_value (struct rtx_iv*,scalar_t__) ; 
 int /*<<< orphan*/  iv_analyze (scalar_t__,scalar_t__,struct rtx_iv*) ; 
 int /*<<< orphan*/  just_once_each_iteration_p (struct loop*,TYPE_1__*) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 scalar_t__ simplify_gen_relational (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 

__attribute__((used)) static rtx
may_unswitch_on (basic_block bb, struct loop *loop, rtx *cinsn)
{
  rtx test, at, op[2], stest;
  struct rtx_iv iv;
  unsigned i;
  enum machine_mode mode;

  /* BB must end in a simple conditional jump.  */
  if (EDGE_COUNT (bb->succs) != 2)
    return NULL_RTX;
  if (!any_condjump_p (BB_END (bb)))
    return NULL_RTX;

  /* With branches inside loop.  */
  if (!flow_bb_inside_loop_p (loop, EDGE_SUCC (bb, 0)->dest)
      || !flow_bb_inside_loop_p (loop, EDGE_SUCC (bb, 1)->dest))
    return NULL_RTX;

  /* It must be executed just once each iteration (because otherwise we
     are unable to update dominator/irreducible loop information correctly).  */
  if (!just_once_each_iteration_p (loop, bb))
    return NULL_RTX;

  /* Condition must be invariant.  */
  test = get_condition (BB_END (bb), &at, true, false);
  if (!test)
    return NULL_RTX;

  for (i = 0; i < 2; i++)
    {
      op[i] = XEXP (test, i);

      if (CONSTANT_P (op[i]))
	continue;

      if (!iv_analyze (at, op[i], &iv))
	return NULL_RTX;
      if (iv.step != const0_rtx
	  || iv.first_special)
	return NULL_RTX;

      op[i] = get_iv_value (&iv, const0_rtx);
    }

  mode = GET_MODE (op[0]);
  if (mode == VOIDmode)
    mode = GET_MODE (op[1]);
  if (GET_MODE_CLASS (mode) == MODE_CC)
    {
      if (at != BB_END (bb))
	return NULL_RTX;

      if (!rtx_equal_p (op[0], XEXP (test, 0))
	  || !rtx_equal_p (op[1], XEXP (test, 1)))
	return NULL_RTX;

      *cinsn = BB_END (bb);
      return test;
    }

  stest = simplify_gen_relational (GET_CODE (test), SImode,
				   mode, op[0], op[1]);
  if (stest == const0_rtx
      || stest == const_true_rtx)
    return stest;

  return canon_condition (gen_rtx_fmt_ee (GET_CODE (test), SImode,
					  op[0], op[1]));
}