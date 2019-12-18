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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_5__ {TYPE_1__* handlers; } ;
struct TYPE_4__ {scalar_t__ insn_code; } ;

/* Variables and functions */
 scalar_t__ CODE_FOR_nothing ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 int /*<<< orphan*/  REAL_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VOID_TYPE ; 
 int /*<<< orphan*/  build_fold_indirect_ref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int expand_twoval_unop (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 
 TYPE_2__* sincos_optab ; 
 int /*<<< orphan*/  validate_arglist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static rtx
expand_builtin_sincos (tree exp)
{
  rtx op0, op1, op2, target1, target2;
  tree arglist = TREE_OPERAND (exp, 1);
  enum machine_mode mode;
  tree arg, sinp, cosp;
  int result;

  if (!validate_arglist (arglist, REAL_TYPE,
			 POINTER_TYPE, POINTER_TYPE, VOID_TYPE))
    return 0;

  arg = TREE_VALUE (arglist);
  sinp = TREE_VALUE (TREE_CHAIN (arglist));
  cosp = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));

  /* Make a suitable register to place result in.  */
  mode = TYPE_MODE (TREE_TYPE (arg));

  /* Check if sincos insn is available, otherwise emit the call.  */
  if (sincos_optab->handlers[(int) mode].insn_code == CODE_FOR_nothing)
    return NULL_RTX;

  target1 = gen_reg_rtx (mode);
  target2 = gen_reg_rtx (mode);

  op0 = expand_normal (arg);
  op1 = expand_normal (build_fold_indirect_ref (sinp));
  op2 = expand_normal (build_fold_indirect_ref (cosp));

  /* Compute into target1 and target2.
     Set TARGET to wherever the result comes back.  */
  result = expand_twoval_unop (sincos_optab, op0, target2, target1, 0);
  gcc_assert (result);

  /* Move target1 and target2 to the memory locations indicated
     by op1 and op2.  */
  emit_move_insn (op1, target1);
  emit_move_insn (op2, target2);

  return const0_rtx;
}