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
typedef  int /*<<< orphan*/  tree ;
typedef  scalar_t__ rtx ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
struct TYPE_8__ {TYPE_2__* handlers; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* type_for_size ) (int,int) ;int /*<<< orphan*/  (* type_for_mode ) (int,int) ;} ;
struct TYPE_7__ {TYPE_1__ types; } ;
struct TYPE_6__ {int /*<<< orphan*/  insn_code; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ABS_EXPR 165 
#define  ADDR_EXPR 164 
#define  ARRAY_RANGE_REF 163 
#define  ARRAY_REF 162 
#define  BIT_AND_EXPR 161 
#define  BIT_FIELD_REF 160 
 int const BIT_XOR_EXPR ; 
 int BLKmode ; 
 int BRANCH_COST ; 
 int /*<<< orphan*/  BUILT_IN_EXPECT ; 
 int /*<<< orphan*/  BUILT_IN_NORMAL ; 
#define  CALL_EXPR 159 
 int /*<<< orphan*/  CODE_FOR_nothing ; 
#define  COMPONENT_REF 158 
#define  COMPOUND_EXPR 157 
#define  COND_EXPR 156 
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
#define  CONVERT_EXPR 155 
 int /*<<< orphan*/  DECL_BUILT_IN_CLASS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_FUNCTION_CODE (int /*<<< orphan*/ ) ; 
 int EQ ; 
#define  EQ_EXPR 154 
#define  ERROR_MARK 153 
 int GE ; 
 int /*<<< orphan*/  GET_CODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 int GEU ; 
#define  GE_EXPR 152 
 int GT ; 
 int GTU ; 
#define  GT_EXPR 151 
 int /*<<< orphan*/  HOST_BITS_PER_WIDE_INT ; 
#define  INTEGER_CST 150 
 int LE ; 
 int LEU ; 
#define  LE_EXPR 149 
#define  LROTATE_EXPR 148 
 int LT ; 
 int LTGT ; 
#define  LTGT_EXPR 147 
 int LTU ; 
#define  LT_EXPR 146 
#define  MINUS_EXPR 145 
 int /*<<< orphan*/  MODE_COMPLEX_FLOAT ; 
 int /*<<< orphan*/  MODE_COMPLEX_INT ; 
 int /*<<< orphan*/  MODE_INT ; 
 int NE ; 
#define  NEGATE_EXPR 144 
#define  NE_EXPR 143 
#define  NON_LVALUE_EXPR 142 
#define  NOP_EXPR 141 
 scalar_t__ NULL_RTX ; 
 int /*<<< orphan*/  NULL_TREE ; 
 int ORDERED ; 
#define  ORDERED_EXPR 140 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
#define  RROTATE_EXPR 139 
 int const RSHIFT_EXPR ; 
 int /*<<< orphan*/  SLOW_BYTE_ACCESS ; 
 int /*<<< orphan*/  SUBREG ; 
 int /*<<< orphan*/  SUBREG_PROMOTED_VAR_P (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int TREE_INT_CST_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_SIDE_EFFECTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TRUTH_ANDIF_EXPR 138 
#define  TRUTH_AND_EXPR 137 
#define  TRUTH_NOT_EXPR 136 
#define  TRUTH_ORIF_EXPR 135 
#define  TRUTH_OR_EXPR 134 
 int TYPE_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PRECISION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_UNSIGNED (int /*<<< orphan*/ ) ; 
 int UNEQ ; 
#define  UNEQ_EXPR 133 
 int UNGE ; 
#define  UNGE_EXPR 132 
 int UNGT ; 
#define  UNGT_EXPR 131 
 int UNLE ; 
#define  UNLE_EXPR 130 
 int UNLT ; 
#define  UNLT_EXPR 129 
 int UNORDERED ; 
#define  UNORDERED_EXPR 128 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst_type (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  can_compare_p (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccp_jump ; 
 TYPE_4__* cmp_optab ; 
 int /*<<< orphan*/  compare_tree_int (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ copy_to_reg (scalar_t__) ; 
 int /*<<< orphan*/  do_compare_and_jump (int /*<<< orphan*/ ,int,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_compare_rtx_and_jump (scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_jump_by_parts_equality (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_jump_by_parts_greater (int /*<<< orphan*/ ,int,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  do_pending_stack_adjust () ; 
 int /*<<< orphan*/  emit_insn (scalar_t__) ; 
 int /*<<< orphan*/  emit_jump (scalar_t__) ; 
 int /*<<< orphan*/  emit_label (scalar_t__) ; 
 int /*<<< orphan*/  error_mark_node ; 
 scalar_t__ expand_builtin_expect_jump (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ expand_normal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_label_rtx () ; 
 int /*<<< orphan*/  get_callee_fndecl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_inner_reference (int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int*,int*,int*,int) ; 
 int /*<<< orphan*/  integer_onep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zerop (int /*<<< orphan*/ ) ; 
 TYPE_3__ lang_hooks ; 
 int mode_for_size (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  prefer_and_bit_test (int,int) ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int) ; 
 int /*<<< orphan*/  stub2 (int,int) ; 
 int tree_floor_log2 (int /*<<< orphan*/ ) ; 

void
do_jump (tree exp, rtx if_false_label, rtx if_true_label)
{
  enum tree_code code = TREE_CODE (exp);
  rtx temp;
  int i;
  tree type;
  enum machine_mode mode;
  rtx drop_through_label = 0;

  switch (code)
    {
    case ERROR_MARK:
      break;

    case INTEGER_CST:
      temp = integer_zerop (exp) ? if_false_label : if_true_label;
      if (temp)
        emit_jump (temp);
      break;

#if 0
      /* This is not true with #pragma weak  */
    case ADDR_EXPR:
      /* The address of something can never be zero.  */
      if (if_true_label)
        emit_jump (if_true_label);
      break;
#endif

    case NOP_EXPR:
      if (TREE_CODE (TREE_OPERAND (exp, 0)) == COMPONENT_REF
          || TREE_CODE (TREE_OPERAND (exp, 0)) == BIT_FIELD_REF
          || TREE_CODE (TREE_OPERAND (exp, 0)) == ARRAY_REF
          || TREE_CODE (TREE_OPERAND (exp, 0)) == ARRAY_RANGE_REF)
        goto normal;
    case CONVERT_EXPR:
      /* If we are narrowing the operand, we have to do the compare in the
         narrower mode.  */
      if ((TYPE_PRECISION (TREE_TYPE (exp))
           < TYPE_PRECISION (TREE_TYPE (TREE_OPERAND (exp, 0)))))
        goto normal;
    case NON_LVALUE_EXPR:
    case ABS_EXPR:
    case NEGATE_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
      /* These cannot change zero->nonzero or vice versa.  */
      do_jump (TREE_OPERAND (exp, 0), if_false_label, if_true_label);
      break;

    case BIT_AND_EXPR:
      /* fold_single_bit_test() converts (X & (1 << C)) into (X >> C) & 1.
	 See if the former is preferred for jump tests and restore it
	 if so.  */
      if (integer_onep (TREE_OPERAND (exp, 1)))
	{
	  tree exp0 = TREE_OPERAND (exp, 0);
	  rtx set_label, clr_label;

	  /* Strip narrowing integral type conversions.  */
	  while ((TREE_CODE (exp0) == NOP_EXPR
		  || TREE_CODE (exp0) == CONVERT_EXPR
		  || TREE_CODE (exp0) == NON_LVALUE_EXPR)
		 && TREE_OPERAND (exp0, 0) != error_mark_node
		 && TYPE_PRECISION (TREE_TYPE (exp0))
		    <= TYPE_PRECISION (TREE_TYPE (TREE_OPERAND (exp0, 0))))
	    exp0 = TREE_OPERAND (exp0, 0);

	  /* "exp0 ^ 1" inverts the sense of the single bit test.  */
	  if (TREE_CODE (exp0) == BIT_XOR_EXPR
	      && integer_onep (TREE_OPERAND (exp0, 1)))
	    {
	      exp0 = TREE_OPERAND (exp0, 0);
	      clr_label = if_true_label;
	      set_label = if_false_label;
	    }
	  else
	    {
	      clr_label = if_false_label;
	      set_label = if_true_label;
	    }

	  if (TREE_CODE (exp0) == RSHIFT_EXPR)
	    {
	      tree arg = TREE_OPERAND (exp0, 0);
	      tree shift = TREE_OPERAND (exp0, 1);
	      tree argtype = TREE_TYPE (arg);
	      if (TREE_CODE (shift) == INTEGER_CST
		  && compare_tree_int (shift, 0) >= 0
		  && compare_tree_int (shift, HOST_BITS_PER_WIDE_INT) < 0
		  && prefer_and_bit_test (TYPE_MODE (argtype),
					  TREE_INT_CST_LOW (shift)))
		{
		  HOST_WIDE_INT mask = (HOST_WIDE_INT) 1
				       << TREE_INT_CST_LOW (shift);
		  do_jump (build2 (BIT_AND_EXPR, argtype, arg,
				   build_int_cst_type (argtype, mask)),
			   clr_label, set_label);
		  break;
		}
	    }
	}

      /* If we are AND'ing with a small constant, do this comparison in the
         smallest type that fits.  If the machine doesn't have comparisons
         that small, it will be converted back to the wider comparison.
         This helps if we are testing the sign bit of a narrower object.
         combine can't do this for us because it can't know whether a
         ZERO_EXTRACT or a compare in a smaller mode exists, but we do.  */

      if (! SLOW_BYTE_ACCESS
          && TREE_CODE (TREE_OPERAND (exp, 1)) == INTEGER_CST
          && TYPE_PRECISION (TREE_TYPE (exp)) <= HOST_BITS_PER_WIDE_INT
          && (i = tree_floor_log2 (TREE_OPERAND (exp, 1))) >= 0
          && (mode = mode_for_size (i + 1, MODE_INT, 0)) != BLKmode
          && (type = lang_hooks.types.type_for_mode (mode, 1)) != 0
          && TYPE_PRECISION (type) < TYPE_PRECISION (TREE_TYPE (exp))
          && (cmp_optab->handlers[(int) TYPE_MODE (type)].insn_code
              != CODE_FOR_nothing))
        {
          do_jump (fold_convert (type, exp), if_false_label, if_true_label);
          break;
        }
      goto normal;

    case TRUTH_NOT_EXPR:
      do_jump (TREE_OPERAND (exp, 0), if_true_label, if_false_label);
      break;

    case COND_EXPR:
      {
	rtx label1 = gen_label_rtx ();
	if (!if_true_label || !if_false_label)
	  {
	    drop_through_label = gen_label_rtx ();
	    if (!if_true_label)
	      if_true_label = drop_through_label;
	    if (!if_false_label)
	      if_false_label = drop_through_label;
	  }

        do_pending_stack_adjust ();
        do_jump (TREE_OPERAND (exp, 0), label1, NULL_RTX);
        do_jump (TREE_OPERAND (exp, 1), if_false_label, if_true_label);
        emit_label (label1);
        do_jump (TREE_OPERAND (exp, 2), if_false_label, if_true_label);
	break;
      }

    case TRUTH_ANDIF_EXPR:
    case TRUTH_ORIF_EXPR:
    case COMPOUND_EXPR:
      /* Lowered by gimplify.c.  */
      gcc_unreachable ();

    case COMPONENT_REF:
    case BIT_FIELD_REF:
    case ARRAY_REF:
    case ARRAY_RANGE_REF:
      {
        HOST_WIDE_INT bitsize, bitpos;
        int unsignedp;
        enum machine_mode mode;
        tree type;
        tree offset;
        int volatilep = 0;

        /* Get description of this reference.  We don't actually care
           about the underlying object here.  */
        get_inner_reference (exp, &bitsize, &bitpos, &offset, &mode,
                             &unsignedp, &volatilep, false);

        type = lang_hooks.types.type_for_size (bitsize, unsignedp);
        if (! SLOW_BYTE_ACCESS
            && type != 0 && bitsize >= 0
            && TYPE_PRECISION (type) < TYPE_PRECISION (TREE_TYPE (exp))
            && (cmp_optab->handlers[(int) TYPE_MODE (type)].insn_code
		!= CODE_FOR_nothing))
          {
            do_jump (fold_convert (type, exp), if_false_label, if_true_label);
            break;
          }
        goto normal;
      }

    case EQ_EXPR:
      {
        tree inner_type = TREE_TYPE (TREE_OPERAND (exp, 0));

        gcc_assert (GET_MODE_CLASS (TYPE_MODE (inner_type))
		    != MODE_COMPLEX_FLOAT);
	gcc_assert (GET_MODE_CLASS (TYPE_MODE (inner_type))
		    != MODE_COMPLEX_INT);
	
        if (integer_zerop (TREE_OPERAND (exp, 1)))
          do_jump (TREE_OPERAND (exp, 0), if_true_label, if_false_label);
        else if (GET_MODE_CLASS (TYPE_MODE (inner_type)) == MODE_INT
                 && !can_compare_p (EQ, TYPE_MODE (inner_type), ccp_jump))
          do_jump_by_parts_equality (exp, if_false_label, if_true_label);
        else
          do_compare_and_jump (exp, EQ, EQ, if_false_label, if_true_label);
        break;
      }

    case MINUS_EXPR:
      /* Nonzero iff operands of minus differ.  */
      exp = build2 (NE_EXPR, TREE_TYPE (exp),
		    TREE_OPERAND (exp, 0),
		    TREE_OPERAND (exp, 1));
      /* FALLTHRU */
    case NE_EXPR:
      {
        tree inner_type = TREE_TYPE (TREE_OPERAND (exp, 0));

        gcc_assert (GET_MODE_CLASS (TYPE_MODE (inner_type))
		    != MODE_COMPLEX_FLOAT);
	gcc_assert (GET_MODE_CLASS (TYPE_MODE (inner_type))
		    != MODE_COMPLEX_INT);
	
        if (integer_zerop (TREE_OPERAND (exp, 1)))
          do_jump (TREE_OPERAND (exp, 0), if_false_label, if_true_label);
        else if (GET_MODE_CLASS (TYPE_MODE (inner_type)) == MODE_INT
           && !can_compare_p (NE, TYPE_MODE (inner_type), ccp_jump))
          do_jump_by_parts_equality (exp, if_true_label, if_false_label);
        else
          do_compare_and_jump (exp, NE, NE, if_false_label, if_true_label);
        break;
      }

    case LT_EXPR:
      mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
      if (GET_MODE_CLASS (mode) == MODE_INT
          && ! can_compare_p (LT, mode, ccp_jump))
        do_jump_by_parts_greater (exp, 1, if_false_label, if_true_label);
      else
        do_compare_and_jump (exp, LT, LTU, if_false_label, if_true_label);
      break;

    case LE_EXPR:
      mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
      if (GET_MODE_CLASS (mode) == MODE_INT
          && ! can_compare_p (LE, mode, ccp_jump))
        do_jump_by_parts_greater (exp, 0, if_true_label, if_false_label);
      else
        do_compare_and_jump (exp, LE, LEU, if_false_label, if_true_label);
      break;

    case GT_EXPR:
      mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
      if (GET_MODE_CLASS (mode) == MODE_INT
          && ! can_compare_p (GT, mode, ccp_jump))
        do_jump_by_parts_greater (exp, 0, if_false_label, if_true_label);
      else
        do_compare_and_jump (exp, GT, GTU, if_false_label, if_true_label);
      break;

    case GE_EXPR:
      mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
      if (GET_MODE_CLASS (mode) == MODE_INT
          && ! can_compare_p (GE, mode, ccp_jump))
        do_jump_by_parts_greater (exp, 1, if_true_label, if_false_label);
      else
        do_compare_and_jump (exp, GE, GEU, if_false_label, if_true_label);
      break;

    case UNORDERED_EXPR:
    case ORDERED_EXPR:
      {
        enum rtx_code cmp, rcmp;
        int do_rev;

        if (code == UNORDERED_EXPR)
          cmp = UNORDERED, rcmp = ORDERED;
        else
          cmp = ORDERED, rcmp = UNORDERED;
        mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));

        do_rev = 0;
        if (! can_compare_p (cmp, mode, ccp_jump)
            && (can_compare_p (rcmp, mode, ccp_jump)
          /* If the target doesn't provide either UNORDERED or ORDERED
             comparisons, canonicalize on UNORDERED for the library.  */
          || rcmp == UNORDERED))
          do_rev = 1;

        if (! do_rev)
          do_compare_and_jump (exp, cmp, cmp, if_false_label, if_true_label);
        else
          do_compare_and_jump (exp, rcmp, rcmp, if_true_label, if_false_label);
      }
      break;

    {
      enum rtx_code rcode1;
      enum tree_code tcode1, tcode2;

      case UNLT_EXPR:
        rcode1 = UNLT;
        tcode1 = UNORDERED_EXPR;
        tcode2 = LT_EXPR;
        goto unordered_bcc;
      case UNLE_EXPR:
        rcode1 = UNLE;
        tcode1 = UNORDERED_EXPR;
        tcode2 = LE_EXPR;
        goto unordered_bcc;
      case UNGT_EXPR:
        rcode1 = UNGT;
        tcode1 = UNORDERED_EXPR;
        tcode2 = GT_EXPR;
        goto unordered_bcc;
      case UNGE_EXPR:
        rcode1 = UNGE;
        tcode1 = UNORDERED_EXPR;
        tcode2 = GE_EXPR;
        goto unordered_bcc;
      case UNEQ_EXPR:
        rcode1 = UNEQ;
        tcode1 = UNORDERED_EXPR;
        tcode2 = EQ_EXPR;
        goto unordered_bcc;
      case LTGT_EXPR:
	/* It is ok for LTGT_EXPR to trap when the result is unordered,
	   so expand to (a < b) || (a > b).  */
        rcode1 = LTGT;
        tcode1 = LT_EXPR;
        tcode2 = GT_EXPR;
        goto unordered_bcc;

      unordered_bcc:
        mode = TYPE_MODE (TREE_TYPE (TREE_OPERAND (exp, 0)));
        if (can_compare_p (rcode1, mode, ccp_jump))
          do_compare_and_jump (exp, rcode1, rcode1, if_false_label,
                               if_true_label);
        else
          {
            tree op0 = save_expr (TREE_OPERAND (exp, 0));
            tree op1 = save_expr (TREE_OPERAND (exp, 1));
            tree cmp0, cmp1;

            /* If the target doesn't support combined unordered
               compares, decompose into two comparisons.  */
	    if (if_true_label == 0)
	      drop_through_label = if_true_label = gen_label_rtx ();
	      
            cmp0 = fold_build2 (tcode1, TREE_TYPE (exp), op0, op1);
            cmp1 = fold_build2 (tcode2, TREE_TYPE (exp), op0, op1);
	    do_jump (cmp0, 0, if_true_label);
	    do_jump (cmp1, if_false_label, if_true_label);
          }
      }
      break;

    case TRUTH_AND_EXPR:
      /* High branch cost, expand as the bitwise AND of the conditions.
	 Do the same if the RHS has side effects, because we're effectively
	 turning a TRUTH_AND_EXPR into a TRUTH_ANDIF_EXPR.  */
      if (BRANCH_COST >= 4 || TREE_SIDE_EFFECTS (TREE_OPERAND (exp, 1)))
	goto normal;

      if (if_false_label == NULL_RTX)
        {
	  drop_through_label = gen_label_rtx ();
          do_jump (TREE_OPERAND (exp, 0), drop_through_label, NULL_RTX);
          do_jump (TREE_OPERAND (exp, 1), NULL_RTX, if_true_label);
	}
      else
	{
	  do_jump (TREE_OPERAND (exp, 0), if_false_label, NULL_RTX);
          do_jump (TREE_OPERAND (exp, 1), if_false_label, if_true_label);
	}
      break;

    case TRUTH_OR_EXPR:
      /* High branch cost, expand as the bitwise OR of the conditions.
	 Do the same if the RHS has side effects, because we're effectively
	 turning a TRUTH_OR_EXPR into a TRUTH_ORIF_EXPR.  */
      if (BRANCH_COST >= 4 || TREE_SIDE_EFFECTS (TREE_OPERAND (exp, 1)))
	goto normal;

      if (if_true_label == NULL_RTX)
	{
          drop_through_label = gen_label_rtx ();
          do_jump (TREE_OPERAND (exp, 0), NULL_RTX, drop_through_label);
          do_jump (TREE_OPERAND (exp, 1), if_false_label, NULL_RTX);
	}
      else
	{
          do_jump (TREE_OPERAND (exp, 0), NULL_RTX, if_true_label);
          do_jump (TREE_OPERAND (exp, 1), if_false_label, if_true_label);
	}
      break;

      /* Special case:
          __builtin_expect (<test>, 0)	and
          __builtin_expect (<test>, 1)

         We need to do this here, so that <test> is not converted to a SCC
         operation on machines that use condition code registers and COMPARE
         like the PowerPC, and then the jump is done based on whether the SCC
         operation produced a 1 or 0.  */
    case CALL_EXPR:
      /* Check for a built-in function.  */
      {
	tree fndecl = get_callee_fndecl (exp);
	tree arglist = TREE_OPERAND (exp, 1);

	if (fndecl
	    && DECL_BUILT_IN_CLASS (fndecl) == BUILT_IN_NORMAL
	    && DECL_FUNCTION_CODE (fndecl) == BUILT_IN_EXPECT
	    && arglist != NULL_TREE
	    && TREE_CHAIN (arglist) != NULL_TREE)
	  {
	    rtx seq = expand_builtin_expect_jump (exp, if_false_label,
						  if_true_label);

	    if (seq != NULL_RTX)
	      {
		emit_insn (seq);
		return;
	      }
	  }
      }
 
      /* Fall through and generate the normal code.  */
    default:
    normal:
      temp = expand_normal (exp);
      do_pending_stack_adjust ();
      /* The RTL optimizers prefer comparisons against pseudos.  */
      if (GET_CODE (temp) == SUBREG)
	{
	  /* Compare promoted variables in their promoted mode.  */
	  if (SUBREG_PROMOTED_VAR_P (temp)
	      && REG_P (XEXP (temp, 0)))
	    temp = XEXP (temp, 0);
	  else
	    temp = copy_to_reg (temp);
	}
      do_compare_rtx_and_jump (temp, CONST0_RTX (GET_MODE (temp)),
			       NE, TYPE_UNSIGNED (TREE_TYPE (exp)),
			       GET_MODE (temp), NULL_RTX,
			       if_false_label, if_true_label);
    }

  if (drop_through_label)
    {
      do_pending_stack_adjust ();
      emit_label (drop_through_label);
    }
}