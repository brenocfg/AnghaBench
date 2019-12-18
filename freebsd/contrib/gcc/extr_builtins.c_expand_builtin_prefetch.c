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
typedef  scalar_t__ tree ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {TYPE_1__* operand; } ;
struct TYPE_3__ {int /*<<< orphan*/  mode; int /*<<< orphan*/  (* predicate ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 scalar_t__ CODE_FOR_prefetch ; 
 int /*<<< orphan*/  EXPAND_NORMAL ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ HAVE_prefetch ; 
 scalar_t__ INTEGER_CST ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int /*<<< orphan*/  POINTER_TYPE ; 
 scalar_t__ Pmode ; 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 scalar_t__ build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 int /*<<< orphan*/  convert_memory_address (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expand_expr (scalar_t__,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (scalar_t__) ; 
 int /*<<< orphan*/  force_reg (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_prefetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* insn_data ; 
 scalar_t__ integer_zero_node ; 
 scalar_t__ side_effects_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  validate_arglist (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
expand_builtin_prefetch (tree arglist)
{
  tree arg0, arg1, arg2;
  rtx op0, op1, op2;

  if (!validate_arglist (arglist, POINTER_TYPE, 0))
    return;

  arg0 = TREE_VALUE (arglist);
  /* Arguments 1 and 2 are optional; argument 1 (read/write) defaults to
     zero (read) and argument 2 (locality) defaults to 3 (high degree of
     locality).  */
  if (TREE_CHAIN (arglist))
    {
      arg1 = TREE_VALUE (TREE_CHAIN (arglist));
      if (TREE_CHAIN (TREE_CHAIN (arglist)))
	arg2 = TREE_VALUE (TREE_CHAIN (TREE_CHAIN (arglist)));
      else
	arg2 = build_int_cst (NULL_TREE, 3);
    }
  else
    {
      arg1 = integer_zero_node;
      arg2 = build_int_cst (NULL_TREE, 3);
    }

  /* Argument 0 is an address.  */
  op0 = expand_expr (arg0, NULL_RTX, Pmode, EXPAND_NORMAL);

  /* Argument 1 (read/write flag) must be a compile-time constant int.  */
  if (TREE_CODE (arg1) != INTEGER_CST)
    {
      error ("second argument to %<__builtin_prefetch%> must be a constant");
      arg1 = integer_zero_node;
    }
  op1 = expand_normal (arg1);
  /* Argument 1 must be either zero or one.  */
  if (INTVAL (op1) != 0 && INTVAL (op1) != 1)
    {
      warning (0, "invalid second argument to %<__builtin_prefetch%>;"
	       " using zero");
      op1 = const0_rtx;
    }

  /* Argument 2 (locality) must be a compile-time constant int.  */
  if (TREE_CODE (arg2) != INTEGER_CST)
    {
      error ("third argument to %<__builtin_prefetch%> must be a constant");
      arg2 = integer_zero_node;
    }
  op2 = expand_normal (arg2);
  /* Argument 2 must be 0, 1, 2, or 3.  */
  if (INTVAL (op2) < 0 || INTVAL (op2) > 3)
    {
      warning (0, "invalid third argument to %<__builtin_prefetch%>; using zero");
      op2 = const0_rtx;
    }

#ifdef HAVE_prefetch
  if (HAVE_prefetch)
    {
      if ((! (*insn_data[(int) CODE_FOR_prefetch].operand[0].predicate)
	     (op0,
	      insn_data[(int) CODE_FOR_prefetch].operand[0].mode))
	  || (GET_MODE (op0) != Pmode))
	{
	  op0 = convert_memory_address (Pmode, op0);
	  op0 = force_reg (Pmode, op0);
	}
      emit_insn (gen_prefetch (op0, op1, op2));
    }
#endif

  /* Don't do anything with direct references to volatile memory, but
     generate code to handle other side effects.  */
  if (!MEM_P (op0) && side_effects_p (op0))
    emit_insn (op0);
}