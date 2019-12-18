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
struct case_node {scalar_t__ low; scalar_t__ high; scalar_t__ code_label; struct case_node* right; } ;
typedef  scalar_t__ rtx ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  bitmap ;
typedef  size_t HOST_WIDE_INT ;

/* Variables and functions */
 int /*<<< orphan*/  BITMAP_ALLOC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BITMAP_FREE (int /*<<< orphan*/ ) ; 
 scalar_t__ CASE_HIGH (scalar_t__) ; 
 scalar_t__ CASE_LABEL (scalar_t__) ; 
 scalar_t__ CASE_LOW (scalar_t__) ; 
 scalar_t__ CASE_USE_BIT_TESTS ; 
 int /*<<< orphan*/  CASE_VECTOR_MODE ; 
 scalar_t__ CASE_VECTOR_PC_RELATIVE ; 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (scalar_t__) ; 
 int /*<<< orphan*/  COMPARE ; 
 scalar_t__ ENUMERAL_TYPE ; 
 int GET_MODE (scalar_t__) ; 
 int GET_MODE_BITSIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE_CLASS (int) ; 
 int GET_MODE_WIDER_MODE (int) ; 
 int /*<<< orphan*/  HAVE_casesi ; 
 int /*<<< orphan*/  HAVE_tablejump ; 
 scalar_t__ INTEGER_CST ; 
 scalar_t__ INT_CST_LT (scalar_t__,scalar_t__) ; 
 scalar_t__ MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  MINUS_EXPR ; 
 scalar_t__ MODE_INT ; 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  Pmode ; 
 int /*<<< orphan*/  SWITCH_BODY (scalar_t__) ; 
 scalar_t__ SWITCH_COND (scalar_t__) ; 
 int SWITCH_LABELS (scalar_t__) ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VEC_ELT (scalar_t__,int) ; 
 int TREE_VEC_LENGTH (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 int VOIDmode ; 
 struct case_node* add_case_node (struct case_node*,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__* alloca (int) ; 
 int /*<<< orphan*/  balance_case_nodes (struct case_node**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bitmap_bit_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bitmap_set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_int_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 unsigned int case_values_threshold () ; 
 scalar_t__ compare_tree_int (scalar_t__,int) ; 
 int /*<<< orphan*/  const0_rtx ; 
 scalar_t__ convert_to_mode (int,scalar_t__,int) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_barrier () ; 
 int /*<<< orphan*/  emit_case_bit_tests (scalar_t__,scalar_t__,scalar_t__,scalar_t__,struct case_node*,scalar_t__) ; 
 int /*<<< orphan*/  emit_case_nodes (scalar_t__,struct case_node*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 int /*<<< orphan*/  emit_jump_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ estimate_case_costs (struct case_node*) ; 
 scalar_t__ expand_normal (scalar_t__) ; 
 int /*<<< orphan*/  flag_jump_tables ; 
 scalar_t__ flag_pic ; 
 scalar_t__ fold_build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  free_temp_slots () ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  gen_rtvec_v (int,scalar_t__*) ; 
 int /*<<< orphan*/  gen_rtx_ADDR_DIFF_VEC (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_ADDR_VEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ gen_rtx_LABEL_REF (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ get_last_insn () ; 
 scalar_t__ have_insn_for (int /*<<< orphan*/ ,int) ; 
 scalar_t__ label_rtx (scalar_t__) ; 
 scalar_t__ lshift_cheap_p () ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ optimize_size ; 
 int /*<<< orphan*/  reorder_insns (scalar_t__,scalar_t__,scalar_t__) ; 
 int squeeze_notes (scalar_t__*,scalar_t__*) ; 
 int /*<<< orphan*/  tree_int_cst_equal (scalar_t__,scalar_t__) ; 
 int tree_low_cst (scalar_t__,int) ; 
 int /*<<< orphan*/  try_casesi (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int try_tablejump (scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__) ; 
 int use_cost_table ; 
 int /*<<< orphan*/  word_mode ; 

void
expand_case (tree exp)
{
  tree minval = NULL_TREE, maxval = NULL_TREE, range = NULL_TREE;
  rtx default_label = 0;
  struct case_node *n;
  unsigned int count, uniq;
  rtx index;
  rtx table_label;
  int ncases;
  rtx *labelvec;
  int i, fail;
  rtx before_case, end, lab;

  tree vec = SWITCH_LABELS (exp);
  tree orig_type = TREE_TYPE (exp);
  tree index_expr = SWITCH_COND (exp);
  tree index_type = TREE_TYPE (index_expr);
  int unsignedp = TYPE_UNSIGNED (index_type);

  /* The insn after which the case dispatch should finally
     be emitted.  Zero for a dummy.  */
  rtx start;

  /* A list of case labels; it is first built as a list and it may then
     be rearranged into a nearly balanced binary tree.  */
  struct case_node *case_list = 0;

  /* Label to jump to if no case matches.  */
  tree default_label_decl;

  /* The switch body is lowered in gimplify.c, we should never have
     switches with a non-NULL SWITCH_BODY here.  */
  gcc_assert (!SWITCH_BODY (exp));
  gcc_assert (SWITCH_LABELS (exp));

  do_pending_stack_adjust ();

  /* An ERROR_MARK occurs for various reasons including invalid data type.  */
  if (index_type != error_mark_node)
    {
      tree elt;
      bitmap label_bitmap;

      /* cleanup_tree_cfg removes all SWITCH_EXPR with their index
	 expressions being INTEGER_CST.  */
      gcc_assert (TREE_CODE (index_expr) != INTEGER_CST);

      /* The default case is at the end of TREE_VEC.  */
      elt = TREE_VEC_ELT (vec, TREE_VEC_LENGTH (vec) - 1);
      gcc_assert (!CASE_HIGH (elt));
      gcc_assert (!CASE_LOW (elt));
      default_label_decl = CASE_LABEL (elt);

      for (i = TREE_VEC_LENGTH (vec) - 1; --i >= 0; )
	{
	  tree low, high;
	  elt = TREE_VEC_ELT (vec, i);

	  low = CASE_LOW (elt);
	  gcc_assert (low);
	  high = CASE_HIGH (elt);

	  /* Discard empty ranges.  */
	  if (high && INT_CST_LT (high, low))
	    continue;

	  case_list = add_case_node (case_list, index_type, low, high,
				     CASE_LABEL (elt));
	}


      before_case = start = get_last_insn ();
      default_label = label_rtx (default_label_decl);

      /* Get upper and lower bounds of case values.  */

      uniq = 0;
      count = 0;
      label_bitmap = BITMAP_ALLOC (NULL);
      for (n = case_list; n; n = n->right)
	{
	  /* Count the elements and track the largest and smallest
	     of them (treating them as signed even if they are not).  */
	  if (count++ == 0)
	    {
	      minval = n->low;
	      maxval = n->high;
	    }
	  else
	    {
	      if (INT_CST_LT (n->low, minval))
		minval = n->low;
	      if (INT_CST_LT (maxval, n->high))
		maxval = n->high;
	    }
	  /* A range counts double, since it requires two compares.  */
	  if (! tree_int_cst_equal (n->low, n->high))
	    count++;

	  /* If we have not seen this label yet, then increase the
	     number of unique case node targets seen.  */
	  lab = label_rtx (n->code_label);
	  if (!bitmap_bit_p (label_bitmap, CODE_LABEL_NUMBER (lab)))
	    {
	      bitmap_set_bit (label_bitmap, CODE_LABEL_NUMBER (lab));
	      uniq++;
	    }
	}

      BITMAP_FREE (label_bitmap);

      /* cleanup_tree_cfg removes all SWITCH_EXPR with a single
	 destination, such as one with a default case only.  However,
	 it doesn't remove cases that are out of range for the switch
	 type, so we may still get a zero here.  */
      if (count == 0)
	{
	  emit_jump (default_label);
	  return;
	}

      /* Compute span of values.  */
      range = fold_build2 (MINUS_EXPR, index_type, maxval, minval);

      /* Try implementing this switch statement by a short sequence of
	 bit-wise comparisons.  However, we let the binary-tree case
	 below handle constant index expressions.  */
      if (CASE_USE_BIT_TESTS
	  && ! TREE_CONSTANT (index_expr)
	  && compare_tree_int (range, GET_MODE_BITSIZE (word_mode)) < 0
	  && compare_tree_int (range, 0) > 0
	  && lshift_cheap_p ()
	  && ((uniq == 1 && count >= 3)
	      || (uniq == 2 && count >= 5)
	      || (uniq == 3 && count >= 6)))
	{
	  /* Optimize the case where all the case values fit in a
	     word without having to subtract MINVAL.  In this case,
	     we can optimize away the subtraction.  */
	  if (compare_tree_int (minval, 0) > 0
	      && compare_tree_int (maxval, GET_MODE_BITSIZE (word_mode)) < 0)
	    {
	      minval = build_int_cst (index_type, 0);
	      range = maxval;
	    }
	  emit_case_bit_tests (index_type, index_expr, minval, range,
			       case_list, default_label);
	}

      /* If range of values is much bigger than number of values,
	 make a sequence of conditional branches instead of a dispatch.
	 If the switch-index is a constant, do it this way
	 because we can optimize it.  */

      else if (count < case_values_threshold ()
	       || compare_tree_int (range,
				    (optimize_size ? 3 : 10) * count) > 0
	       /* RANGE may be signed, and really large ranges will show up
		  as negative numbers.  */
	       || compare_tree_int (range, 0) < 0
#ifndef ASM_OUTPUT_ADDR_DIFF_ELT
	       || flag_pic
#endif
	       || !flag_jump_tables
	       || TREE_CONSTANT (index_expr)
	       /* If neither casesi or tablejump is available, we can
		  only go this way.  */
	       || (!HAVE_casesi && !HAVE_tablejump))
	{
	  index = expand_normal (index_expr);

	  /* If the index is a short or char that we do not have
	     an insn to handle comparisons directly, convert it to
	     a full integer now, rather than letting each comparison
	     generate the conversion.  */

	  if (GET_MODE_CLASS (GET_MODE (index)) == MODE_INT
	      && ! have_insn_for (COMPARE, GET_MODE (index)))
	    {
	      enum machine_mode wider_mode;
	      for (wider_mode = GET_MODE (index); wider_mode != VOIDmode;
		   wider_mode = GET_MODE_WIDER_MODE (wider_mode))
		if (have_insn_for (COMPARE, wider_mode))
		  {
		    index = convert_to_mode (wider_mode, index, unsignedp);
		    break;
		  }
	    }

	  do_pending_stack_adjust ();

	  if (MEM_P (index))
	    index = copy_to_reg (index);

	  /* We generate a binary decision tree to select the
	     appropriate target code.  This is done as follows:

	     The list of cases is rearranged into a binary tree,
	     nearly optimal assuming equal probability for each case.

	     The tree is transformed into RTL, eliminating
	     redundant test conditions at the same time.

	     If program flow could reach the end of the
	     decision tree an unconditional jump to the
	     default code is emitted.  */

	  use_cost_table
	    = (TREE_CODE (orig_type) != ENUMERAL_TYPE
	       && estimate_case_costs (case_list));
	  balance_case_nodes (&case_list, NULL);
	  emit_case_nodes (index, case_list, default_label, index_type);
	  emit_jump (default_label);
	}
      else
	{
	  table_label = gen_label_rtx ();
	  if (! try_casesi (index_type, index_expr, minval, range,
			    table_label, default_label))
	    {
	      bool ok;

	      /* Index jumptables from zero for suitable values of
                 minval to avoid a subtraction.  */
	      if (! optimize_size
		  && compare_tree_int (minval, 0) > 0
		  && compare_tree_int (minval, 3) < 0)
		{
		  minval = build_int_cst (index_type, 0);
		  range = maxval;
		}

	      ok = try_tablejump (index_type, index_expr, minval, range,
				  table_label, default_label);
	      gcc_assert (ok);
	    }

	  /* Get table of labels to jump to, in order of case index.  */

	  ncases = tree_low_cst (range, 0) + 1;
	  labelvec = alloca (ncases * sizeof (rtx));
	  memset (labelvec, 0, ncases * sizeof (rtx));

	  for (n = case_list; n; n = n->right)
	    {
	      /* Compute the low and high bounds relative to the minimum
		 value since that should fit in a HOST_WIDE_INT while the
		 actual values may not.  */
	      HOST_WIDE_INT i_low
		= tree_low_cst (fold_build2 (MINUS_EXPR, index_type,
					     n->low, minval), 1);
	      HOST_WIDE_INT i_high
		= tree_low_cst (fold_build2 (MINUS_EXPR, index_type,
					     n->high, minval), 1);
	      HOST_WIDE_INT i;

	      for (i = i_low; i <= i_high; i ++)
		labelvec[i]
		  = gen_rtx_LABEL_REF (Pmode, label_rtx (n->code_label));
	    }

	  /* Fill in the gaps with the default.  */
	  for (i = 0; i < ncases; i++)
	    if (labelvec[i] == 0)
	      labelvec[i] = gen_rtx_LABEL_REF (Pmode, default_label);

	  /* Output the table.  */
	  emit_label (table_label);

	  if (CASE_VECTOR_PC_RELATIVE || flag_pic)
	    emit_jump_insn (gen_rtx_ADDR_DIFF_VEC (CASE_VECTOR_MODE,
						   gen_rtx_LABEL_REF (Pmode, table_label),
						   gen_rtvec_v (ncases, labelvec),
						   const0_rtx, const0_rtx));
	  else
	    emit_jump_insn (gen_rtx_ADDR_VEC (CASE_VECTOR_MODE,
					      gen_rtvec_v (ncases, labelvec)));

	  /* Record no drop-through after the table.  */
	  emit_barrier ();
	}

      before_case = NEXT_INSN (before_case);
      end = get_last_insn ();
      fail = squeeze_notes (&before_case, &end);
      gcc_assert (!fail);
      reorder_insns (before_case, end, start);
    }

  free_temp_slots ();
}