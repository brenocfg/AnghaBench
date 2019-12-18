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
typedef  int /*<<< orphan*/ * tree ;

/* Variables and functions */
#define  ABS_EXPR 262 
#define  ADDR_EXPR 261 
#define  ALIGN_INDIRECT_REF 260 
#define  ARRAY_RANGE_REF 259 
#define  ARRAY_REF 258 
#define  ASM_EXPR 257 
#define  BIND_EXPR 256 
#define  BIT_AND_EXPR 255 
#define  BIT_FIELD_REF 254 
#define  BIT_IOR_EXPR 253 
#define  BIT_NOT_EXPR 252 
#define  BIT_XOR_EXPR 251 
#define  BLOCK 250 
#define  BUILT_IN_CONSTANT_P 249 
#define  BUILT_IN_EXPECT 248 
 int /*<<< orphan*/  BUILT_IN_NORMAL ; 
#define  CALL_EXPR 247 
#define  CASE_LABEL_EXPR 246 
#define  CATCH_EXPR 245 
#define  CEIL_DIV_EXPR 244 
#define  CEIL_MOD_EXPR 243 
#define  COMPLEX_CST 242 
#define  COMPLEX_EXPR 241 
#define  COMPONENT_REF 240 
#define  COMPOUND_EXPR 239 
#define  COND_EXPR 238 
#define  CONJ_EXPR 237 
 scalar_t__ CONSTANT_CLASS_P (int /*<<< orphan*/ *) ; 
#define  CONSTRUCTOR 236 
#define  CONVERT_EXPR 235 
 int /*<<< orphan*/ * DECL_ARGUMENTS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECL_BUILT_IN_CLASS (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DECL_FUNCTION_CODE (int /*<<< orphan*/ *) ; 
#define  DOT_PROD_EXPR 234 
#define  EH_FILTER_EXPR 233 
#define  EQ_EXPR 232 
#define  ERROR_MARK 231 
#define  EXACT_DIV_EXPR 230 
#define  EXC_PTR_EXPR 229 
#define  EXIT_EXPR 228 
#define  FDESC_EXPR 227 
#define  FILTER_EXPR 226 
#define  FIX_CEIL_EXPR 225 
#define  FIX_FLOOR_EXPR 224 
#define  FIX_ROUND_EXPR 223 
#define  FIX_TRUNC_EXPR 222 
#define  FLOAT_EXPR 221 
#define  FLOOR_DIV_EXPR 220 
#define  FLOOR_MOD_EXPR 219 
#define  GE_EXPR 218 
#define  GOTO_EXPR 217 
#define  GT_EXPR 216 
#define  IDENTIFIER_NODE 215 
#define  INDIRECT_REF 214 
#define  INIT_EXPR 213 
#define  INTEGER_CST 212 
 scalar_t__ IS_TYPE_OR_DECL_P (int /*<<< orphan*/ *) ; 
#define  LABEL_EXPR 211 
#define  LE_EXPR 210 
#define  LOOP_EXPR 209 
#define  LROTATE_EXPR 208 
#define  LSHIFT_EXPR 207 
#define  LTGT_EXPR 206 
#define  LT_EXPR 205 
#define  MAX_EXPR 204 
#define  MINUS_EXPR 203 
#define  MIN_EXPR 202 
#define  MISALIGNED_INDIRECT_REF 201 
#define  MODIFY_EXPR 200 
#define  MULT_EXPR 199 
#define  NEGATE_EXPR 198 
#define  NE_EXPR 197 
#define  NON_LVALUE_EXPR 196 
#define  NOP_EXPR 195 
 int /*<<< orphan*/ * NULL_TREE ; 
#define  OBJ_TYPE_REF 194 
#define  OMP_ATOMIC 193 
#define  OMP_CLAUSE 192 
#define  OMP_CONTINUE 191 
#define  OMP_CRITICAL 190 
#define  OMP_FOR 189 
#define  OMP_MASTER 188 
#define  OMP_ORDERED 187 
#define  OMP_PARALLEL 186 
#define  OMP_RETURN 185 
#define  OMP_SECTION 184 
#define  OMP_SECTIONS 183 
#define  OMP_SINGLE 182 
#define  ORDERED_EXPR 181 
 int /*<<< orphan*/  PARAM_INLINE_CALL_COST ; 
 int PARAM_VALUE (int /*<<< orphan*/ ) ; 
#define  PHI_NODE 180 
#define  PLUS_EXPR 179 
#define  POSTDECREMENT_EXPR 178 
#define  POSTINCREMENT_EXPR 177 
#define  PREDECREMENT_EXPR 176 
#define  PREINCREMENT_EXPR 175 
#define  RANGE_EXPR 174 
#define  RDIV_EXPR 173 
#define  REALIGN_LOAD_EXPR 172 
#define  REAL_CST 171 
#define  REDUC_MAX_EXPR 170 
#define  REDUC_MIN_EXPR 169 
#define  REDUC_PLUS_EXPR 168 
 scalar_t__ REFERENCE_CLASS_P (int /*<<< orphan*/ *) ; 
#define  RESX_EXPR 167 
#define  RETURN_EXPR 166 
#define  ROUND_DIV_EXPR 165 
#define  ROUND_MOD_EXPR 164 
#define  RROTATE_EXPR 163 
#define  RSHIFT_EXPR 162 
#define  SAVE_EXPR 161 
#define  SSA_NAME 160 
#define  STATEMENT_LIST 159 
#define  STRING_CST 158 
#define  SWITCH_EXPR 157 
#define  TARGET_EXPR 156 
 int /*<<< orphan*/ * TREE_CHAIN (int /*<<< orphan*/ *) ; 
 int TREE_CODE (int /*<<< orphan*/ *) ; 
#define  TREE_LIST 155 
 int /*<<< orphan*/ * TREE_OPERAND (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * TREE_VALUE (int /*<<< orphan*/ *) ; 
#define  TREE_VEC 154 
#define  TRUNC_DIV_EXPR 153 
#define  TRUNC_MOD_EXPR 152 
#define  TRUTH_ANDIF_EXPR 151 
#define  TRUTH_AND_EXPR 150 
#define  TRUTH_NOT_EXPR 149 
#define  TRUTH_ORIF_EXPR 148 
#define  TRUTH_OR_EXPR 147 
#define  TRUTH_XOR_EXPR 146 
#define  TRY_CATCH_EXPR 145 
#define  TRY_FINALLY_EXPR 144 
#define  UNEQ_EXPR 143 
#define  UNGE_EXPR 142 
#define  UNGT_EXPR 141 
#define  UNLE_EXPR 140 
#define  UNLT_EXPR 139 
#define  UNORDERED_EXPR 138 
#define  VA_ARG_EXPR 137 
#define  VECTOR_CST 136 
#define  VEC_COND_EXPR 135 
#define  VEC_LSHIFT_EXPR 134 
#define  VEC_RSHIFT_EXPR 133 
#define  VIEW_CONVERT_EXPR 132 
#define  WIDEN_MULT_EXPR 131 
#define  WIDEN_SUM_EXPR 130 
#define  WITH_CLEANUP_EXPR 129 
#define  WITH_SIZE_EXPR 128 
 int estimate_move_cost (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * get_callee_fndecl (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_gimple_reg (int /*<<< orphan*/ *) ; 

__attribute__((used)) static tree
estimate_num_insns_1 (tree *tp, int *walk_subtrees, void *data)
{
  int *count = (int *) data;
  tree x = *tp;

  if (IS_TYPE_OR_DECL_P (x))
    {
      *walk_subtrees = 0;
      return NULL;
    }
  /* Assume that constants and references counts nothing.  These should
     be majorized by amount of operations among them we count later
     and are common target of CSE and similar optimizations.  */
  else if (CONSTANT_CLASS_P (x) || REFERENCE_CLASS_P (x))
    return NULL;

  switch (TREE_CODE (x))
    {
    /* Containers have no cost.  */
    case TREE_LIST:
    case TREE_VEC:
    case BLOCK:
    case COMPONENT_REF:
    case BIT_FIELD_REF:
    case INDIRECT_REF:
    case ALIGN_INDIRECT_REF:
    case MISALIGNED_INDIRECT_REF:
    case ARRAY_REF:
    case ARRAY_RANGE_REF:
    case OBJ_TYPE_REF:
    case EXC_PTR_EXPR: /* ??? */
    case FILTER_EXPR: /* ??? */
    case COMPOUND_EXPR:
    case BIND_EXPR:
    case WITH_CLEANUP_EXPR:
    case NOP_EXPR:
    case VIEW_CONVERT_EXPR:
    case SAVE_EXPR:
    case ADDR_EXPR:
    case COMPLEX_EXPR:
    case RANGE_EXPR:
    case CASE_LABEL_EXPR:
    case SSA_NAME:
    case CATCH_EXPR:
    case EH_FILTER_EXPR:
    case STATEMENT_LIST:
    case ERROR_MARK:
    case NON_LVALUE_EXPR:
    case FDESC_EXPR:
    case VA_ARG_EXPR:
    case TRY_CATCH_EXPR:
    case TRY_FINALLY_EXPR:
    case LABEL_EXPR:
    case GOTO_EXPR:
    case RETURN_EXPR:
    case EXIT_EXPR:
    case LOOP_EXPR:
    case PHI_NODE:
    case WITH_SIZE_EXPR:
    case OMP_CLAUSE:
    case OMP_RETURN:
    case OMP_CONTINUE:
      break;

    /* We don't account constants for now.  Assume that the cost is amortized
       by operations that do use them.  We may re-consider this decision once
       we are able to optimize the tree before estimating its size and break
       out static initializers.  */
    case IDENTIFIER_NODE:
    case INTEGER_CST:
    case REAL_CST:
    case COMPLEX_CST:
    case VECTOR_CST:
    case STRING_CST:
      *walk_subtrees = 0;
      return NULL;

    /* Try to estimate the cost of assignments.  We have three cases to
       deal with:
	1) Simple assignments to registers;
	2) Stores to things that must live in memory.  This includes
	   "normal" stores to scalars, but also assignments of large
	   structures, or constructors of big arrays;
	3) TARGET_EXPRs.

       Let us look at the first two cases, assuming we have "a = b + C":
       <modify_expr <var_decl "a"> <plus_expr <var_decl "b"> <constant C>>
       If "a" is a GIMPLE register, the assignment to it is free on almost
       any target, because "a" usually ends up in a real register.  Hence
       the only cost of this expression comes from the PLUS_EXPR, and we
       can ignore the MODIFY_EXPR.
       If "a" is not a GIMPLE register, the assignment to "a" will most
       likely be a real store, so the cost of the MODIFY_EXPR is the cost
       of moving something into "a", which we compute using the function
       estimate_move_cost.

       The third case deals with TARGET_EXPRs, for which the semantics are
       that a temporary is assigned, unless the TARGET_EXPR itself is being
       assigned to something else.  In the latter case we do not need the
       temporary.  E.g. in <modify_expr <var_decl "a"> <target_expr>>, the
       MODIFY_EXPR is free.  */
    case INIT_EXPR:
    case MODIFY_EXPR:
      /* Is the right and side a TARGET_EXPR?  */
      if (TREE_CODE (TREE_OPERAND (x, 1)) == TARGET_EXPR)
	break;
      /* ... fall through ...  */

    case TARGET_EXPR:
      x = TREE_OPERAND (x, 0);
      /* Is this an assignments to a register?  */
      if (is_gimple_reg (x))
	break;
      /* Otherwise it's a store, so fall through to compute the move cost.  */

    case CONSTRUCTOR:
      *count += estimate_move_cost (TREE_TYPE (x));
      break;

    /* Assign cost of 1 to usual operations.
       ??? We may consider mapping RTL costs to this.  */
    case COND_EXPR:
    case VEC_COND_EXPR:

    case PLUS_EXPR:
    case MINUS_EXPR:
    case MULT_EXPR:

    case FIX_TRUNC_EXPR:
    case FIX_CEIL_EXPR:
    case FIX_FLOOR_EXPR:
    case FIX_ROUND_EXPR:

    case NEGATE_EXPR:
    case FLOAT_EXPR:
    case MIN_EXPR:
    case MAX_EXPR:
    case ABS_EXPR:

    case LSHIFT_EXPR:
    case RSHIFT_EXPR:
    case LROTATE_EXPR:
    case RROTATE_EXPR:
    case VEC_LSHIFT_EXPR:
    case VEC_RSHIFT_EXPR:

    case BIT_IOR_EXPR:
    case BIT_XOR_EXPR:
    case BIT_AND_EXPR:
    case BIT_NOT_EXPR:

    case TRUTH_ANDIF_EXPR:
    case TRUTH_ORIF_EXPR:
    case TRUTH_AND_EXPR:
    case TRUTH_OR_EXPR:
    case TRUTH_XOR_EXPR:
    case TRUTH_NOT_EXPR:

    case LT_EXPR:
    case LE_EXPR:
    case GT_EXPR:
    case GE_EXPR:
    case EQ_EXPR:
    case NE_EXPR:
    case ORDERED_EXPR:
    case UNORDERED_EXPR:

    case UNLT_EXPR:
    case UNLE_EXPR:
    case UNGT_EXPR:
    case UNGE_EXPR:
    case UNEQ_EXPR:
    case LTGT_EXPR:

    case CONVERT_EXPR:

    case CONJ_EXPR:

    case PREDECREMENT_EXPR:
    case PREINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
    case POSTINCREMENT_EXPR:

    case SWITCH_EXPR:

    case ASM_EXPR:

    case REALIGN_LOAD_EXPR:

    case REDUC_MAX_EXPR:
    case REDUC_MIN_EXPR:
    case REDUC_PLUS_EXPR:
    case WIDEN_SUM_EXPR:
    case DOT_PROD_EXPR: 

    case WIDEN_MULT_EXPR:

    case RESX_EXPR:
      *count += 1;
      break;

    /* Few special cases of expensive operations.  This is useful
       to avoid inlining on functions having too many of these.  */
    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case EXACT_DIV_EXPR:
    case TRUNC_MOD_EXPR:
    case CEIL_MOD_EXPR:
    case FLOOR_MOD_EXPR:
    case ROUND_MOD_EXPR:
    case RDIV_EXPR:
      *count += 10;
      break;
    case CALL_EXPR:
      {
	tree decl = get_callee_fndecl (x);
	tree arg;

	if (decl && DECL_BUILT_IN_CLASS (decl) == BUILT_IN_NORMAL)
	  switch (DECL_FUNCTION_CODE (decl))
	    {
	    case BUILT_IN_CONSTANT_P:
	      *walk_subtrees = 0;
	      return NULL_TREE;
	    case BUILT_IN_EXPECT:
	      return NULL_TREE;
	    default:
	      break;
	    }

	/* Our cost must be kept in sync with cgraph_estimate_size_after_inlining
	   that does use function declaration to figure out the arguments.  */
	if (!decl)
	  {
	    for (arg = TREE_OPERAND (x, 1); arg; arg = TREE_CHAIN (arg))
	      *count += estimate_move_cost (TREE_TYPE (TREE_VALUE (arg)));
	  }
	else
	  {
	    for (arg = DECL_ARGUMENTS (decl); arg; arg = TREE_CHAIN (arg))
	      *count += estimate_move_cost (TREE_TYPE (arg));
	  }

	*count += PARAM_VALUE (PARAM_INLINE_CALL_COST);
	break;
      }

    case OMP_PARALLEL:
    case OMP_FOR:
    case OMP_SECTIONS:
    case OMP_SINGLE:
    case OMP_SECTION:
    case OMP_MASTER:
    case OMP_ORDERED:
    case OMP_CRITICAL:
    case OMP_ATOMIC:
      /* OpenMP directives are generally very expensive.  */
      *count += 40;
      break;

    default:
      gcc_unreachable ();
    }
  return NULL;
}