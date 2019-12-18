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
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 int BLKmode ; 
 scalar_t__ ERROR_MARK ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ GET_MODE_BITSIZE (int) ; 
 scalar_t__ HAVE_canonicalize_funcptr_for_compare ; 
 scalar_t__ INTEGER_CST ; 
 int /*<<< orphan*/  NULL_RTX ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_compare_rtx_and_jump (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  expr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_canonicalize_funcptr_for_compare (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_reg_rtx (int) ; 

__attribute__((used)) static void
do_compare_and_jump (tree exp, enum rtx_code signed_code,
		     enum rtx_code unsigned_code, rtx if_false_label,
		     rtx if_true_label)
{
  rtx op0, op1;
  tree type;
  enum machine_mode mode;
  int unsignedp;
  enum rtx_code code;

  /* Don't crash if the comparison was erroneous.  */
  op0 = expand_normal (TREE_OPERAND (exp, 0));
  if (TREE_CODE (TREE_OPERAND (exp, 0)) == ERROR_MARK)
    return;

  op1 = expand_normal (TREE_OPERAND (exp, 1));
  if (TREE_CODE (TREE_OPERAND (exp, 1)) == ERROR_MARK)
    return;

  type = TREE_TYPE (TREE_OPERAND (exp, 0));
  mode = TYPE_MODE (type);
  if (TREE_CODE (TREE_OPERAND (exp, 0)) == INTEGER_CST
      && (TREE_CODE (TREE_OPERAND (exp, 1)) != INTEGER_CST
          || (GET_MODE_BITSIZE (mode)
              > GET_MODE_BITSIZE (TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp,
                                                                      1)))))))
    {
      /* op0 might have been replaced by promoted constant, in which
         case the type of second argument should be used.  */
      type = TREE_TYPE (TREE_OPERAND (exp, 1));
      mode = TYPE_MODE (type);
    }
  unsignedp = TYPE_UNSIGNED (type);
  code = unsignedp ? unsigned_code : signed_code;

#ifdef HAVE_canonicalize_funcptr_for_compare
  /* If function pointers need to be "canonicalized" before they can
     be reliably compared, then canonicalize them.
     Only do this if *both* sides of the comparison are function pointers.
     If one side isn't, we want a noncanonicalized comparison.  See PR
     middle-end/17564.  */
  if (HAVE_canonicalize_funcptr_for_compare
      && TREE_CODE (TREE_TYPE (TREE_OPERAND (exp, 0))) == POINTER_TYPE
      && TREE_CODE (TREE_TYPE (TREE_TYPE (TREE_OPERAND (exp, 0))))
          == FUNCTION_TYPE
      && TREE_CODE (TREE_TYPE (TREE_OPERAND (exp, 1))) == POINTER_TYPE
      && TREE_CODE (TREE_TYPE (TREE_TYPE (TREE_OPERAND (exp, 1))))
          == FUNCTION_TYPE)
    {
      rtx new_op0 = gen_reg_rtx (mode);
      rtx new_op1 = gen_reg_rtx (mode);

      emit_insn (gen_canonicalize_funcptr_for_compare (new_op0, op0));
      op0 = new_op0;

      emit_insn (gen_canonicalize_funcptr_for_compare (new_op1, op1));
      op1 = new_op1;
    }
#endif

  do_compare_rtx_and_jump (op0, op1, code, unsignedp, mode,
                           ((mode == BLKmode)
                            ? expr_size (TREE_OPERAND (exp, 0)) : NULL_RTX),
                           if_false_label, if_true_label);
}