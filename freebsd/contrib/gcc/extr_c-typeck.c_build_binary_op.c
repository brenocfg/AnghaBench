#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_2__ {char* (* invalid_binary_op ) (int,scalar_t__,scalar_t__) ;} ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 int ADDR_EXPR ; 
#define  BIT_AND_EXPR 153 
#define  BIT_IOR_EXPR 152 
 scalar_t__ BIT_NOT_EXPR ; 
#define  BIT_XOR_EXPR 151 
 int BLOCK_POINTER_TYPE ; 
#define  CEIL_DIV_EXPR 150 
 int /*<<< orphan*/  COMPLETE_TYPE_P (scalar_t__) ; 
 int COMPLEX_TYPE ; 
 int /*<<< orphan*/  DECL_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_WEAK (scalar_t__) ; 
 scalar_t__ ENUMERAL_TYPE ; 
#define  EQ_EXPR 149 
 int ERROR_MARK ; 
#define  EXACT_DIV_EXPR 148 
#define  FLOOR_DIV_EXPR 147 
#define  FLOOR_MOD_EXPR 146 
 int FUNCTION_TYPE ; 
#define  GE_EXPR 145 
#define  GT_EXPR 144 
 int HOST_BITS_PER_WIDE_INT ; 
 scalar_t__ INTEGER_CST ; 
 int INTEGER_TYPE ; 
 int LABEL_DECL ; 
#define  LE_EXPR 143 
#define  LSHIFT_EXPR 142 
#define  LT_EXPR 141 
#define  MINUS_EXPR 140 
#define  MULT_EXPR 139 
#define  NE_EXPR 138 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Waddress ; 
 int /*<<< orphan*/  OPT_Wdiv_by_zero ; 
 int /*<<< orphan*/  OPT_Wfloat_equal ; 
 int PARM_DECL ; 
#define  PLUS_EXPR 137 
 int POINTER_TYPE ; 
 int RDIV_EXPR ; 
 int REAL_TYPE ; 
#define  ROUND_DIV_EXPR 136 
#define  RSHIFT_EXPR 135 
 int /*<<< orphan*/  STRIP_TYPE_NOPS (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TRUNC_DIV_EXPR 134 
#define  TRUNC_MOD_EXPR 133 
#define  TRUTH_ANDIF_EXPR 132 
#define  TRUTH_AND_EXPR 131 
#define  TRUTH_ORIF_EXPR 130 
#define  TRUTH_OR_EXPR 129 
#define  TRUTH_XOR_EXPR 128 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 int TYPE_PRECISION (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 int VECTOR_TYPE ; 
 int /*<<< orphan*/  VOID_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  binary_op_error (int,scalar_t__,scalar_t__) ; 
 scalar_t__ c_common_signed_or_unsigned_type (int,scalar_t__) ; 
 scalar_t__ c_common_signed_type (scalar_t__) ; 
 scalar_t__ c_common_truthvalue_conversion (scalar_t__) ; 
 scalar_t__ c_common_type (scalar_t__,scalar_t__) ; 
 scalar_t__ common_pointer_type (scalar_t__,scalar_t__) ; 
 scalar_t__ common_type (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  comp_target_types (scalar_t__,scalar_t__) ; 
 scalar_t__ compare_tree_int (scalar_t__,int) ; 
 scalar_t__ convert (scalar_t__,scalar_t__) ; 
 scalar_t__ convert_and_check (scalar_t__,scalar_t__) ; 
 scalar_t__ default_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char const*,char*) ; 
 scalar_t__ error_mark_node ; 
 int /*<<< orphan*/  extra_warnings ; 
 scalar_t__ fold_build2 (int,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2_initializer (int,scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ get_narrower (scalar_t__,int*) ; 
 scalar_t__ host_integerp (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ int_fits_type_p (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  integer_all_onesp (scalar_t__) ; 
 scalar_t__ integer_type_node ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  null_pointer_constant_p (scalar_t__) ; 
 int objc_compare_types (scalar_t__,scalar_t__,int,scalar_t__,char*) ; 
 int /*<<< orphan*/  pedantic ; 
 int /*<<< orphan*/  pedwarn (char*) ; 
 scalar_t__ pointer_diff (scalar_t__,scalar_t__) ; 
 scalar_t__ pointer_int_sum (int const,scalar_t__,scalar_t__) ; 
 scalar_t__ ptr_type_node ; 
 scalar_t__ require_constant_value ; 
 int /*<<< orphan*/  same_scalar_type_ignoring_signedness (scalar_t__,scalar_t__) ; 
 scalar_t__ shorten_compare (scalar_t__*,scalar_t__*,scalar_t__*,int*) ; 
 scalar_t__ skip_evaluation ; 
 char* stub1 (int,scalar_t__,scalar_t__) ; 
 TYPE_1__ targetm ; 
 scalar_t__ tree_expr_nonnegative_warnv_p (scalar_t__,int*) ; 
 int /*<<< orphan*/  tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_int_cst_sgn (scalar_t__) ; 
 int tree_low_cst (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ warn_sign_compare ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*,...) ; 

tree
build_binary_op (enum tree_code code, tree orig_op0, tree orig_op1,
		 int convert_p)
{
  tree type0, type1;
  enum tree_code code0, code1;
  tree op0, op1;
  const char *invalid_op_diag;

  /* Expression code to give to the expression when it is built.
     Normally this is CODE, which is what the caller asked for,
     but in some special cases we change it.  */
  enum tree_code resultcode = code;

  /* Data type in which the computation is to be performed.
     In the simplest cases this is the common type of the arguments.  */
  tree result_type = NULL;

  /* Nonzero means operands have already been type-converted
     in whatever way is necessary.
     Zero means they need to be converted to RESULT_TYPE.  */
  int converted = 0;

  /* Nonzero means create the expression with this type, rather than
     RESULT_TYPE.  */
  tree build_type = 0;

  /* Nonzero means after finally constructing the expression
     convert it to this type.  */
  tree final_type = 0;

  /* Nonzero if this is an operation like MIN or MAX which can
     safely be computed in short if both args are promoted shorts.
     Also implies COMMON.
     -1 indicates a bitwise operation; this makes a difference
     in the exact conditions for when it is safe to do the operation
     in a narrower mode.  */
  int shorten = 0;

  /* Nonzero if this is a comparison operation;
     if both args are promoted shorts, compare the original shorts.
     Also implies COMMON.  */
  int short_compare = 0;

  /* Nonzero if this is a right-shift operation, which can be computed on the
     original short and then promoted if the operand is a promoted short.  */
  int short_shift = 0;

  /* Nonzero means set RESULT_TYPE to the common type of the args.  */
  int common = 0;

  /* True means types are compatible as far as ObjC is concerned.  */
  bool objc_ok;

  if (convert_p)
    {
      op0 = default_conversion (orig_op0);
      op1 = default_conversion (orig_op1);
    }
  else
    {
      op0 = orig_op0;
      op1 = orig_op1;
    }

  type0 = TREE_TYPE (op0);
  type1 = TREE_TYPE (op1);

  /* The expression codes of the data types of the arguments tell us
     whether the arguments are integers, floating, pointers, etc.  */
  code0 = TREE_CODE (type0);
  code1 = TREE_CODE (type1);

  /* Strip NON_LVALUE_EXPRs, etc., since we aren't using as an lvalue.  */
  STRIP_TYPE_NOPS (op0);
  STRIP_TYPE_NOPS (op1);

  /* If an error was already reported for one of the arguments,
     avoid reporting another error.  */

  if (code0 == ERROR_MARK || code1 == ERROR_MARK)
    return error_mark_node;

  if ((invalid_op_diag
       = targetm.invalid_binary_op (code, type0, type1)))
    {
      error (invalid_op_diag, "");
      return error_mark_node;
    }

  objc_ok = objc_compare_types (type0, type1, -3, NULL_TREE, "comparison");

  switch (code)
    {
    case PLUS_EXPR:
      /* Handle the pointer + int case.  */
      if (code0 == POINTER_TYPE && code1 == INTEGER_TYPE)
	return pointer_int_sum (PLUS_EXPR, op0, op1);
      else if (code1 == POINTER_TYPE && code0 == INTEGER_TYPE)
	return pointer_int_sum (PLUS_EXPR, op1, op0);
      else
	common = 1;
      break;

    case MINUS_EXPR:
      /* Subtraction of two similar pointers.
	 We must subtract them as integers, then divide by object size.  */
      if (code0 == POINTER_TYPE && code1 == POINTER_TYPE
	  && comp_target_types (type0, type1))
	return pointer_diff (op0, op1);
      /* Handle pointer minus int.  Just like pointer plus int.  */
      else if (code0 == POINTER_TYPE && code1 == INTEGER_TYPE)
	return pointer_int_sum (MINUS_EXPR, op0, op1);
      else
	common = 1;
      break;

    case MULT_EXPR:
      common = 1;
      break;

    case TRUNC_DIV_EXPR:
    case CEIL_DIV_EXPR:
    case FLOOR_DIV_EXPR:
    case ROUND_DIV_EXPR:
    case EXACT_DIV_EXPR:
      /* Floating point division by zero is a legitimate way to obtain
	 infinities and NaNs.  */
      if (skip_evaluation == 0 && integer_zerop (op1))
	warning (OPT_Wdiv_by_zero, "division by zero");

      if ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE))
	{
	  enum tree_code tcode0 = code0, tcode1 = code1;

	  if (code0 == COMPLEX_TYPE || code0 == VECTOR_TYPE)
	    tcode0 = TREE_CODE (TREE_TYPE (TREE_TYPE (op0)));
	  if (code1 == COMPLEX_TYPE || code1 == VECTOR_TYPE)
	    tcode1 = TREE_CODE (TREE_TYPE (TREE_TYPE (op1)));

	  if (!(tcode0 == INTEGER_TYPE && tcode1 == INTEGER_TYPE))
	    resultcode = RDIV_EXPR;
	  else
	    /* Although it would be tempting to shorten always here, that
	       loses on some targets, since the modulo instruction is
	       undefined if the quotient can't be represented in the
	       computation mode.  We shorten only if unsigned or if
	       dividing by something we know != -1.  */
	    shorten = (TYPE_UNSIGNED (TREE_TYPE (orig_op0))
		       || (TREE_CODE (op1) == INTEGER_CST
			   && !integer_all_onesp (op1)));
	  common = 1;
	}
      break;

    case BIT_AND_EXPR:
    case BIT_IOR_EXPR:
    case BIT_XOR_EXPR:
      if (code0 == INTEGER_TYPE && code1 == INTEGER_TYPE)
	shorten = -1;
      else if (code0 == VECTOR_TYPE && code1 == VECTOR_TYPE)
	common = 1;
      break;

    case TRUNC_MOD_EXPR:
    case FLOOR_MOD_EXPR:
      if (skip_evaluation == 0 && integer_zerop (op1))
	warning (OPT_Wdiv_by_zero, "division by zero");

      if (code0 == INTEGER_TYPE && code1 == INTEGER_TYPE)
	{
	  /* Although it would be tempting to shorten always here, that loses
	     on some targets, since the modulo instruction is undefined if the
	     quotient can't be represented in the computation mode.  We shorten
	     only if unsigned or if dividing by something we know != -1.  */
	  shorten = (TYPE_UNSIGNED (TREE_TYPE (orig_op0))
		     || (TREE_CODE (op1) == INTEGER_CST
			 && !integer_all_onesp (op1)));
	  common = 1;
	}
      break;

    case TRUTH_ANDIF_EXPR:
    case TRUTH_ORIF_EXPR:
    case TRUTH_AND_EXPR:
    case TRUTH_OR_EXPR:
    case TRUTH_XOR_EXPR:
      if ((code0 == INTEGER_TYPE || code0 == POINTER_TYPE
	   /* APPLE LOCAL radar 5928316 */
	   || code0 == BLOCK_POINTER_TYPE
	   || code0 == REAL_TYPE || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == POINTER_TYPE
	      /* APPLE LOCAL radar 5928316 */
	      || code1 == BLOCK_POINTER_TYPE
	      || code1 == REAL_TYPE || code1 == COMPLEX_TYPE))
	{
	  /* Result of these operations is always an int,
	     but that does not mean the operands should be
	     converted to ints!  */
	  result_type = integer_type_node;
	  op0 = c_common_truthvalue_conversion (op0);
	  op1 = c_common_truthvalue_conversion (op1);
	  converted = 1;
	}
      break;

      /* Shift operations: result has same type as first operand;
	 always convert second operand to int.
	 Also set SHORT_SHIFT if shifting rightward.  */

    case RSHIFT_EXPR:
      if (code0 == INTEGER_TYPE && code1 == INTEGER_TYPE)
	{
	  if (TREE_CODE (op1) == INTEGER_CST && skip_evaluation == 0)
	    {
	      if (tree_int_cst_sgn (op1) < 0)
		warning (0, "right shift count is negative");
	      else
		{
		  if (!integer_zerop (op1))
		    short_shift = 1;

		  if (compare_tree_int (op1, TYPE_PRECISION (type0)) >= 0)
		    warning (0, "right shift count >= width of type");
		}
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Convert the shift-count to an integer, regardless of size
	     of value being shifted.  */
	  if (TYPE_MAIN_VARIANT (TREE_TYPE (op1)) != integer_type_node)
	    op1 = convert (integer_type_node, op1);
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      break;

    case LSHIFT_EXPR:
      if (code0 == INTEGER_TYPE && code1 == INTEGER_TYPE)
	{
	  if (TREE_CODE (op1) == INTEGER_CST && skip_evaluation == 0)
	    {
	      if (tree_int_cst_sgn (op1) < 0)
		warning (0, "left shift count is negative");

	      else if (compare_tree_int (op1, TYPE_PRECISION (type0)) >= 0)
		warning (0, "left shift count >= width of type");
	    }

	  /* Use the type of the value to be shifted.  */
	  result_type = type0;
	  /* Convert the shift-count to an integer, regardless of size
	     of value being shifted.  */
	  if (TYPE_MAIN_VARIANT (TREE_TYPE (op1)) != integer_type_node)
	    op1 = convert (integer_type_node, op1);
	  /* Avoid converting op1 to result_type later.  */
	  converted = 1;
	}
      break;

    case EQ_EXPR:
    case NE_EXPR:
      if (code0 == REAL_TYPE || code1 == REAL_TYPE)
	warning (OPT_Wfloat_equal,
		 "comparing floating point with == or != is unsafe");
      /* Result of comparison is always int,
	 but don't convert the args to int!  */
      build_type = integer_type_node;
      if ((code0 == INTEGER_TYPE || code0 == REAL_TYPE
	   || code0 == COMPLEX_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE
	      || code1 == COMPLEX_TYPE))
	short_compare = 1;
      /* APPLE LOCAL begin blocks 6065211 */
      else if ((code0 == POINTER_TYPE || code0 == BLOCK_POINTER_TYPE)
	       && (code1 == POINTER_TYPE || code1 == BLOCK_POINTER_TYPE))
      /* APPLE LOCAL end blocks 6065211 */
	{
	  tree tt0 = TREE_TYPE (type0);
	  tree tt1 = TREE_TYPE (type1);
	  /* Anything compares with void *.  void * compares with anything.
	     Otherwise, the targets must be compatible
	     and both must be object or both incomplete.  */
	  if (comp_target_types (type0, type1))
	    result_type = common_pointer_type (type0, type1);
	  /* APPLE LOCAL begin blocks 6065211 */
	  else if (code1 == BLOCK_POINTER_TYPE && VOID_TYPE_P (tt0))
	    ;
	  else if (code0 == BLOCK_POINTER_TYPE && VOID_TYPE_P (tt1))
	    ;
	  /* APPLE LOCAL end blocks 6065211 */
	  else if (VOID_TYPE_P (tt0))
	    {
	      /* op0 != orig_op0 detects the case of something
		 whose value is 0 but which isn't a valid null ptr const.  */
	      if (pedantic && !null_pointer_constant_p (orig_op0)
		  && TREE_CODE (tt1) == FUNCTION_TYPE)
		pedwarn ("ISO C forbids comparison of %<void *%>"
			 " with function pointer");
	    }
	  else if (VOID_TYPE_P (tt1))
	    {
	      if (pedantic && !null_pointer_constant_p (orig_op1)
		  && TREE_CODE (tt0) == FUNCTION_TYPE)
		pedwarn ("ISO C forbids comparison of %<void *%>"
			 " with function pointer");
	    }
	  else
	    /* Avoid warning about the volatile ObjC EH puts on decls.  */
	    if (!objc_ok)
	      /* APPLE LOCAL begin blocks 6065211 */
	      {
		if (code0 == BLOCK_POINTER_TYPE || code1 == BLOCK_POINTER_TYPE)
		  pedwarn ("comparison of distinct block types lacks a cast");
		else
		  pedwarn ("comparison of distinct pointer types lacks a cast");
	      }
	      /* APPLE LOCAL end blocks 6065211 */

	  if (result_type == NULL_TREE)
	    result_type = ptr_type_node;
	}
      else if (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  if (TREE_CODE (op0) == ADDR_EXPR
	      && DECL_P (TREE_OPERAND (op0, 0))
	      && (TREE_CODE (TREE_OPERAND (op0, 0)) == PARM_DECL
		  || TREE_CODE (TREE_OPERAND (op0, 0)) == LABEL_DECL
		  || !DECL_WEAK (TREE_OPERAND (op0, 0))))
	    warning (OPT_Waddress, "the address of %qD will never be NULL",
		     TREE_OPERAND (op0, 0));
	  result_type = type0;
	}
      else if (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  if (TREE_CODE (op1) == ADDR_EXPR
	      && DECL_P (TREE_OPERAND (op1, 0))
	      && (TREE_CODE (TREE_OPERAND (op1, 0)) == PARM_DECL
		  || TREE_CODE (TREE_OPERAND (op1, 0)) == LABEL_DECL
		  || !DECL_WEAK (TREE_OPERAND (op1, 0))))
	    warning (OPT_Waddress, "the address of %qD will never be NULL",
		     TREE_OPERAND (op1, 0));
	  result_type = type1;
	}
      else if (code0 == POINTER_TYPE && code1 == INTEGER_TYPE)
	{
	  result_type = type0;
	  pedwarn ("comparison between pointer and integer");
	}
      else if (code0 == INTEGER_TYPE && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn ("comparison between pointer and integer");
	}
      /* APPLE LOCAL begin radar 5732232 - blocks (C++ cl) */
      else if (code0 == BLOCK_POINTER_TYPE && null_pointer_constant_p (orig_op1))
	 result_type = type0;
      else if (code1 == BLOCK_POINTER_TYPE && null_pointer_constant_p (orig_op0))
	 result_type = type1;
      /* APPLE LOCAL end radar 5732232 - blocks (C++ cl) */
      break;

    case LE_EXPR:
    case GE_EXPR:
    case LT_EXPR:
    case GT_EXPR:
      build_type = integer_type_node;
      if ((code0 == INTEGER_TYPE || code0 == REAL_TYPE)
	  && (code1 == INTEGER_TYPE || code1 == REAL_TYPE))
	short_compare = 1;
      else if (code0 == POINTER_TYPE && code1 == POINTER_TYPE)
	{
	  if (comp_target_types (type0, type1))
	    {
	      result_type = common_pointer_type (type0, type1);
	      if (!COMPLETE_TYPE_P (TREE_TYPE (type0))
		  != !COMPLETE_TYPE_P (TREE_TYPE (type1)))
		pedwarn ("comparison of complete and incomplete pointers");
	      else if (pedantic
		       && TREE_CODE (TREE_TYPE (type0)) == FUNCTION_TYPE)
		pedwarn ("ISO C forbids ordered comparisons of pointers to functions");
	    }
	  else
	    {
	      result_type = ptr_type_node;
	      pedwarn ("comparison of distinct pointer types lacks a cast");
	    }
	}
      else if (code0 == POINTER_TYPE && null_pointer_constant_p (orig_op1))
	{
	  result_type = type0;
	  if (pedantic || extra_warnings)
	    pedwarn ("ordered comparison of pointer with integer zero");
	}
      else if (code1 == POINTER_TYPE && null_pointer_constant_p (orig_op0))
	{
	  result_type = type1;
	  if (pedantic)
	    pedwarn ("ordered comparison of pointer with integer zero");
	}
      else if (code0 == POINTER_TYPE && code1 == INTEGER_TYPE)
	{
	  result_type = type0;
	  pedwarn ("comparison between pointer and integer");
	}
      else if (code0 == INTEGER_TYPE && code1 == POINTER_TYPE)
	{
	  result_type = type1;
	  pedwarn ("comparison between pointer and integer");
	}
      break;

    default:
      gcc_unreachable ();
    }

  if (code0 == ERROR_MARK || code1 == ERROR_MARK)
    return error_mark_node;

  if (code0 == VECTOR_TYPE && code1 == VECTOR_TYPE
      && (!tree_int_cst_equal (TYPE_SIZE (type0), TYPE_SIZE (type1))
	  || !same_scalar_type_ignoring_signedness (TREE_TYPE (type0),
						    TREE_TYPE (type1))))
    {
      binary_op_error (code, type0, type1);
      return error_mark_node;
    }

  if ((code0 == INTEGER_TYPE || code0 == REAL_TYPE || code0 == COMPLEX_TYPE
       || code0 == VECTOR_TYPE)
      &&
      (code1 == INTEGER_TYPE || code1 == REAL_TYPE || code1 == COMPLEX_TYPE
       || code1 == VECTOR_TYPE))
    {
      int none_complex = (code0 != COMPLEX_TYPE && code1 != COMPLEX_TYPE);

      if (shorten || common || short_compare)
	result_type = c_common_type (type0, type1);

      /* For certain operations (which identify themselves by shorten != 0)
	 if both args were extended from the same smaller type,
	 do the arithmetic in that type and then extend.

	 shorten !=0 and !=1 indicates a bitwise operation.
	 For them, this optimization is safe only if
	 both args are zero-extended or both are sign-extended.
	 Otherwise, we might change the result.
	 Eg, (short)-1 | (unsigned short)-1 is (int)-1
	 but calculated in (unsigned short) it would be (unsigned short)-1.  */

      if (shorten && none_complex)
	{
	  int unsigned0, unsigned1;
	  tree arg0, arg1;
	  int uns;
	  tree type;

	  /* Cast OP0 and OP1 to RESULT_TYPE.  Doing so prevents
	     excessive narrowing when we call get_narrower below.  For
	     example, suppose that OP0 is of unsigned int extended
	     from signed char and that RESULT_TYPE is long long int.
	     If we explicitly cast OP0 to RESULT_TYPE, OP0 would look
	     like

	       (long long int) (unsigned int) signed_char

	     which get_narrower would narrow down to

	       (unsigned int) signed char

	     If we do not cast OP0 first, get_narrower would return
	     signed_char, which is inconsistent with the case of the
	     explicit cast.  */
	  op0 = convert (result_type, op0);
	  op1 = convert (result_type, op1);

	  arg0 = get_narrower (op0, &unsigned0);
	  arg1 = get_narrower (op1, &unsigned1);

	  /* UNS is 1 if the operation to be done is an unsigned one.  */
	  uns = TYPE_UNSIGNED (result_type);

	  final_type = result_type;

	  /* Handle the case that OP0 (or OP1) does not *contain* a conversion
	     but it *requires* conversion to FINAL_TYPE.  */

	  if ((TYPE_PRECISION (TREE_TYPE (op0))
	       == TYPE_PRECISION (TREE_TYPE (arg0)))
	      && TREE_TYPE (op0) != final_type)
	    unsigned0 = TYPE_UNSIGNED (TREE_TYPE (op0));
	  if ((TYPE_PRECISION (TREE_TYPE (op1))
	       == TYPE_PRECISION (TREE_TYPE (arg1)))
	      && TREE_TYPE (op1) != final_type)
	    unsigned1 = TYPE_UNSIGNED (TREE_TYPE (op1));

	  /* Now UNSIGNED0 is 1 if ARG0 zero-extends to FINAL_TYPE.  */

	  /* For bitwise operations, signedness of nominal type
	     does not matter.  Consider only how operands were extended.  */
	  if (shorten == -1)
	    uns = unsigned0;

	  /* Note that in all three cases below we refrain from optimizing
	     an unsigned operation on sign-extended args.
	     That would not be valid.  */

	  /* Both args variable: if both extended in same way
	     from same width, do it in that width.
	     Do it unsigned if args were zero-extended.  */
	  if ((TYPE_PRECISION (TREE_TYPE (arg0))
	       < TYPE_PRECISION (result_type))
	      && (TYPE_PRECISION (TREE_TYPE (arg1))
		  == TYPE_PRECISION (TREE_TYPE (arg0)))
	      && unsigned0 == unsigned1
	      && (unsigned0 || !uns))
	    result_type
	      = c_common_signed_or_unsigned_type
	      (unsigned0, common_type (TREE_TYPE (arg0), TREE_TYPE (arg1)));
	  else if (TREE_CODE (arg0) == INTEGER_CST
		   && (unsigned1 || !uns)
		   && (TYPE_PRECISION (TREE_TYPE (arg1))
		       < TYPE_PRECISION (result_type))
		   && (type
		       = c_common_signed_or_unsigned_type (unsigned1,
							   TREE_TYPE (arg1)),
		       int_fits_type_p (arg0, type)))
	    result_type = type;
	  else if (TREE_CODE (arg1) == INTEGER_CST
		   && (unsigned0 || !uns)
		   && (TYPE_PRECISION (TREE_TYPE (arg0))
		       < TYPE_PRECISION (result_type))
		   && (type
		       = c_common_signed_or_unsigned_type (unsigned0,
							   TREE_TYPE (arg0)),
		       int_fits_type_p (arg1, type)))
	    result_type = type;
	}

      /* Shifts can be shortened if shifting right.  */

      if (short_shift)
	{
	  int unsigned_arg;
	  tree arg0 = get_narrower (op0, &unsigned_arg);

	  final_type = result_type;

	  if (arg0 == op0 && final_type == TREE_TYPE (op0))
	    unsigned_arg = TYPE_UNSIGNED (TREE_TYPE (op0));

	  if (TYPE_PRECISION (TREE_TYPE (arg0)) < TYPE_PRECISION (result_type)
	      /* We can shorten only if the shift count is less than the
		 number of bits in the smaller type size.  */
	      && compare_tree_int (op1, TYPE_PRECISION (TREE_TYPE (arg0))) < 0
	      /* We cannot drop an unsigned shift after sign-extension.  */
	      && (!TYPE_UNSIGNED (final_type) || unsigned_arg))
	    {
	      /* Do an unsigned shift if the operand was zero-extended.  */
	      result_type
		= c_common_signed_or_unsigned_type (unsigned_arg,
						    TREE_TYPE (arg0));
	      /* Convert value-to-be-shifted to that type.  */
	      if (TREE_TYPE (op0) != result_type)
		op0 = convert (result_type, op0);
	      converted = 1;
	    }
	}

      /* Comparison operations are shortened too but differently.
	 They identify themselves by setting short_compare = 1.  */

      if (short_compare)
	{
	  /* Don't write &op0, etc., because that would prevent op0
	     from being kept in a register.
	     Instead, make copies of the our local variables and
	     pass the copies by reference, then copy them back afterward.  */
	  tree xop0 = op0, xop1 = op1, xresult_type = result_type;
	  enum tree_code xresultcode = resultcode;
	  tree val
	    = shorten_compare (&xop0, &xop1, &xresult_type, &xresultcode);

	  if (val != 0)
	    return val;

	  op0 = xop0, op1 = xop1;
	  converted = 1;
	  resultcode = xresultcode;

	  if (warn_sign_compare && skip_evaluation == 0)
	    {
	      int op0_signed = !TYPE_UNSIGNED (TREE_TYPE (orig_op0));
	      int op1_signed = !TYPE_UNSIGNED (TREE_TYPE (orig_op1));
	      int unsignedp0, unsignedp1;
	      tree primop0 = get_narrower (op0, &unsignedp0);
	      tree primop1 = get_narrower (op1, &unsignedp1);

	      xop0 = orig_op0;
	      xop1 = orig_op1;
	      STRIP_TYPE_NOPS (xop0);
	      STRIP_TYPE_NOPS (xop1);

	      /* Give warnings for comparisons between signed and unsigned
		 quantities that may fail.

		 Do the checking based on the original operand trees, so that
		 casts will be considered, but default promotions won't be.

		 Do not warn if the comparison is being done in a signed type,
		 since the signed type will only be chosen if it can represent
		 all the values of the unsigned type.  */
	      if (!TYPE_UNSIGNED (result_type))
		/* OK */;
	      /* Do not warn if both operands are the same signedness.  */
	      else if (op0_signed == op1_signed)
		/* OK */;
	      else
		{
		  tree sop, uop;
		  bool ovf;

		  if (op0_signed)
		    sop = xop0, uop = xop1;
		  else
		    sop = xop1, uop = xop0;

		  /* Do not warn if the signed quantity is an
		     unsuffixed integer literal (or some static
		     constant expression involving such literals or a
		     conditional expression involving such literals)
		     and it is non-negative.  */
		  if (tree_expr_nonnegative_warnv_p (sop, &ovf))
		    /* OK */;
		  /* Do not warn if the comparison is an equality operation,
		     the unsigned quantity is an integral constant, and it
		     would fit in the result if the result were signed.  */
		  else if (TREE_CODE (uop) == INTEGER_CST
			   && (resultcode == EQ_EXPR || resultcode == NE_EXPR)
			   && int_fits_type_p
			   (uop, c_common_signed_type (result_type)))
		    /* OK */;
		  /* Do not warn if the unsigned quantity is an enumeration
		     constant and its maximum value would fit in the result
		     if the result were signed.  */
		  else if (TREE_CODE (uop) == INTEGER_CST
			   && TREE_CODE (TREE_TYPE (uop)) == ENUMERAL_TYPE
			   && int_fits_type_p
			   (TYPE_MAX_VALUE (TREE_TYPE (uop)),
			    c_common_signed_type (result_type)))
		    /* OK */;
		  else
		    warning (0, "comparison between signed and unsigned");
		}

	      /* Warn if two unsigned values are being compared in a size
		 larger than their original size, and one (and only one) is the
		 result of a `~' operator.  This comparison will always fail.

		 Also warn if one operand is a constant, and the constant
		 does not have all bits set that are set in the ~ operand
		 when it is extended.  */

	      if ((TREE_CODE (primop0) == BIT_NOT_EXPR)
		  != (TREE_CODE (primop1) == BIT_NOT_EXPR))
		{
		  if (TREE_CODE (primop0) == BIT_NOT_EXPR)
		    primop0 = get_narrower (TREE_OPERAND (primop0, 0),
					    &unsignedp0);
		  else
		    primop1 = get_narrower (TREE_OPERAND (primop1, 0),
					    &unsignedp1);

		  if (host_integerp (primop0, 0) || host_integerp (primop1, 0))
		    {
		      tree primop;
		      HOST_WIDE_INT constant, mask;
		      int unsignedp, bits;

		      if (host_integerp (primop0, 0))
			{
			  primop = primop1;
			  unsignedp = unsignedp1;
			  constant = tree_low_cst (primop0, 0);
			}
		      else
			{
			  primop = primop0;
			  unsignedp = unsignedp0;
			  constant = tree_low_cst (primop1, 0);
			}

		      bits = TYPE_PRECISION (TREE_TYPE (primop));
		      if (bits < TYPE_PRECISION (result_type)
			  && bits < HOST_BITS_PER_WIDE_INT && unsignedp)
			{
			  mask = (~(HOST_WIDE_INT) 0) << bits;
			  if ((mask & constant) != mask)
			    warning (0, "comparison of promoted ~unsigned with constant");
			}
		    }
		  else if (unsignedp0 && unsignedp1
			   && (TYPE_PRECISION (TREE_TYPE (primop0))
			       < TYPE_PRECISION (result_type))
			   && (TYPE_PRECISION (TREE_TYPE (primop1))
			       < TYPE_PRECISION (result_type)))
		    warning (0, "comparison of promoted ~unsigned with unsigned");
		}
	    }
	}
    }

  /* At this point, RESULT_TYPE must be nonzero to avoid an error message.
     If CONVERTED is zero, both args will be converted to type RESULT_TYPE.
     Then the expression will be built.
     It will be given type FINAL_TYPE if that is nonzero;
     otherwise, it will be given type RESULT_TYPE.  */

  if (!result_type)
    {
      binary_op_error (code, TREE_TYPE (op0), TREE_TYPE (op1));
      return error_mark_node;
    }

  if (!converted)
    {
      if (TREE_TYPE (op0) != result_type)
	op0 = convert_and_check (result_type, op0);
      if (TREE_TYPE (op1) != result_type)
	op1 = convert_and_check (result_type, op1);

      /* This can happen if one operand has a vector type, and the other
	 has a different type.  */
      if (TREE_CODE (op0) == ERROR_MARK || TREE_CODE (op1) == ERROR_MARK)
	return error_mark_node;
    }

  if (build_type == NULL_TREE)
    build_type = result_type;

  {
    /* Treat expressions in initializers specially as they can't trap.  */
    tree result = require_constant_value ? fold_build2_initializer (resultcode,
								    build_type,
								    op0, op1)
					 : fold_build2 (resultcode, build_type,
							op0, op1);

    if (final_type != 0)
      result = convert (final_type, result);
    return result;
  }
}