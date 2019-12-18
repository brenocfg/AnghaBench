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
struct case_node {int /*<<< orphan*/  high; int /*<<< orphan*/  low; int /*<<< orphan*/  code_label; struct case_node* right; } ;
struct case_bit_test {scalar_t__ label; unsigned int hi; unsigned int lo; int bits; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  struct case_node* case_node_ptr ;
typedef  unsigned int HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  GTU ; 
 unsigned int HOST_BITS_PER_INT ; 
 unsigned int HOST_BITS_PER_WIDE_INT ; 
 int MAX_CASE_BIT_TESTS ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 int /*<<< orphan*/  NE ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  OPTAB_WIDEN ; 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  and_optab ; 
 int /*<<< orphan*/  ashl_optab ; 
 int /*<<< orphan*/  case_bit_test_cmp ; 
 scalar_t__ const0_rtx ; 
 scalar_t__ const1_rtx ; 
 scalar_t__ convert_to_mode (int,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_cmp_and_jump_insns (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,scalar_t__) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 scalar_t__ expand_binop (int,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ immed_double_const (unsigned int,unsigned int,int) ; 
 scalar_t__ label_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  qsort (struct case_bit_test*,unsigned int,int,int /*<<< orphan*/ ) ; 
 unsigned int tree_low_cst (int /*<<< orphan*/ ,int) ; 
 int word_mode ; 

__attribute__((used)) static void
emit_case_bit_tests (tree index_type, tree index_expr, tree minval,
		     tree range, case_node_ptr nodes, rtx default_label)
{
  struct case_bit_test test[MAX_CASE_BIT_TESTS];
  enum machine_mode mode;
  rtx expr, index, label;
  unsigned int i,j,lo,hi;
  struct case_node *n;
  unsigned int count;

  count = 0;
  for (n = nodes; n; n = n->right)
    {
      label = label_rtx (n->code_label);
      for (i = 0; i < count; i++)
	if (label == test[i].label)
	  break;

      if (i == count)
	{
	  gcc_assert (count < MAX_CASE_BIT_TESTS);
	  test[i].hi = 0;
	  test[i].lo = 0;
	  test[i].label = label;
	  test[i].bits = 1;
	  count++;
	}
      else
        test[i].bits++;

      lo = tree_low_cst (fold_build2 (MINUS_EXPR, index_type,
				      n->low, minval), 1);
      hi = tree_low_cst (fold_build2 (MINUS_EXPR, index_type,
				      n->high, minval), 1);
      for (j = lo; j <= hi; j++)
        if (j >= HOST_BITS_PER_WIDE_INT)
	  test[i].hi |= (HOST_WIDE_INT) 1 << (j - HOST_BITS_PER_INT);
	else
	  test[i].lo |= (HOST_WIDE_INT) 1 << j;
    }

  qsort (test, count, sizeof(*test), case_bit_test_cmp);

  index_expr = fold_build2 (MINUS_EXPR, index_type,
			    fold_convert (index_type, index_expr),
			    fold_convert (index_type, minval));
  index = expand_normal (index_expr);
  do_pending_stack_adjust ();

  mode = TYPE_MODE (index_type);
  expr = expand_normal (range);
  emit_cmp_and_jump_insns (index, expr, GTU, NULL_RTX, mode, 1,
			   default_label);

  index = convert_to_mode (word_mode, index, 0);
  index = expand_binop (word_mode, ashl_optab, const1_rtx,
			index, NULL_RTX, 1, OPTAB_WIDEN);

  for (i = 0; i < count; i++)
    {
      expr = immed_double_const (test[i].lo, test[i].hi, word_mode);
      expr = expand_binop (word_mode, and_optab, index, expr,
			   NULL_RTX, 1, OPTAB_WIDEN);
      emit_cmp_and_jump_insns (expr, const0_rtx, NE, NULL_RTX,
			       word_mode, 1, test[i].label);
    }

  emit_jump (default_label);
}