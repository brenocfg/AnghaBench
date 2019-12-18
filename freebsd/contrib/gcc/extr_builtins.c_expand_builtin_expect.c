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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  NOTE_EXPECTED_VALUE ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 scalar_t__ GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NOTE_INSN_EXPECTED_VALUE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ NULL_TREE ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_note (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_guess_branch_prob ; 
 int /*<<< orphan*/  force_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_EQ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ integer_zero_node ; 

__attribute__((used)) static rtx
expand_builtin_expect (tree arglist, rtx target)
{
  tree exp, c;
  rtx note, rtx_c;

  if (arglist == NULL_TREE
      || TREE_CHAIN (arglist) == NULL_TREE)
    return const0_rtx;
  exp = TREE_VALUE (arglist);
  c = TREE_VALUE (TREE_CHAIN (arglist));

  if (TREE_CODE (c) != INTEGER_CST)
    {
      error ("second argument to %<__builtin_expect%> must be a constant");
      c = integer_zero_node;
    }

  target = expand_expr (exp, target, VOIDmode, EXPAND_NORMAL);

  /* Don't bother with expected value notes for integral constants.  */
  if (flag_guess_branch_prob && GET_CODE (target) != CONST_INT)
    {
      /* We do need to force this into a register so that we can be
	 moderately sure to be able to correctly interpret the branch
	 condition later.  */
      target = force_reg (GET_MODE (target), target);

      rtx_c = expand_expr (c, NULL_RTX, GET_MODE (target), EXPAND_NORMAL);

      note = emit_note (NOTE_INSN_EXPECTED_VALUE);
      NOTE_EXPECTED_VALUE (note) = gen_rtx_EQ (VOIDmode, target, rtx_c);
    }

  return target;
}