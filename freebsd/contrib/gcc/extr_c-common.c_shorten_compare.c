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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;

/* Variables and functions */
 int /*<<< orphan*/  COMPOUND_EXPR ; 
 scalar_t__ DECIMAL_FLOAT_MODE_P (int /*<<< orphan*/ ) ; 
 int EQ_EXPR ; 
#define  GE_EXPR 131 
#define  GT_EXPR 130 
 scalar_t__ INTEGER_CST ; 
 int INT_CST_LT (scalar_t__,scalar_t__) ; 
 int INT_CST_LT_UNSIGNED (scalar_t__,scalar_t__) ; 
#define  LE_EXPR 129 
#define  LT_EXPR 128 
 int NE_EXPR ; 
 scalar_t__ REAL_TYPE ; 
 scalar_t__ TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_CONSTANT (scalar_t__) ; 
 int /*<<< orphan*/  TREE_CONSTANT_OVERFLOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_HIGH (scalar_t__) ; 
 int /*<<< orphan*/  TREE_INT_CST_LOW (scalar_t__) ; 
 int /*<<< orphan*/  TREE_OVERFLOW (scalar_t__) ; 
 scalar_t__ TREE_SIDE_EFFECTS (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAX_VALUE (scalar_t__) ; 
 scalar_t__ TYPE_MIN_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MODE (scalar_t__) ; 
 scalar_t__ TYPE_PRECISION (scalar_t__) ; 
 int TYPE_UNSIGNED (scalar_t__) ; 
 scalar_t__ build2 (int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_int_cst_wide (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ c_common_signed_or_unsigned_type (int,scalar_t__) ; 
 scalar_t__ c_common_signed_type (scalar_t__) ; 
 scalar_t__ c_common_unsigned_type (scalar_t__) ; 
 scalar_t__ common_type (scalar_t__,scalar_t__) ; 
 scalar_t__ convert (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  extra_warnings ; 
 scalar_t__ force_fit_type (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ get_narrower (scalar_t__,int*) ; 
 int /*<<< orphan*/  in_system_header ; 
 scalar_t__ integer_zerop (scalar_t__) ; 
 int /*<<< orphan*/  real_zerop (scalar_t__) ; 
 scalar_t__ truthvalue_false_node ; 
 scalar_t__ truthvalue_true_node ; 
 scalar_t__ truthvalue_type_node ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
shorten_compare (tree *op0_ptr, tree *op1_ptr, tree *restype_ptr,
		 enum tree_code *rescode_ptr)
{
  tree type;
  tree op0 = *op0_ptr;
  tree op1 = *op1_ptr;
  int unsignedp0, unsignedp1;
  int real1, real2;
  tree primop0, primop1;
  enum tree_code code = *rescode_ptr;

  /* Throw away any conversions to wider types
     already present in the operands.  */

  primop0 = get_narrower (op0, &unsignedp0);
  primop1 = get_narrower (op1, &unsignedp1);

  /* Handle the case that OP0 does not *contain* a conversion
     but it *requires* conversion to FINAL_TYPE.  */

  if (op0 == primop0 && TREE_TYPE (op0) != *restype_ptr)
    unsignedp0 = TYPE_UNSIGNED (TREE_TYPE (op0));
  if (op1 == primop1 && TREE_TYPE (op1) != *restype_ptr)
    unsignedp1 = TYPE_UNSIGNED (TREE_TYPE (op1));

  /* If one of the operands must be floated, we cannot optimize.  */
  real1 = TREE_CODE (TREE_TYPE (primop0)) == REAL_TYPE;
  real2 = TREE_CODE (TREE_TYPE (primop1)) == REAL_TYPE;

  /* If first arg is constant, swap the args (changing operation
     so value is preserved), for canonicalization.  Don't do this if
     the second arg is 0.  */

  if (TREE_CONSTANT (primop0)
      && !integer_zerop (primop1) && !real_zerop (primop1))
    {
      tree tem = primop0;
      int temi = unsignedp0;
      primop0 = primop1;
      primop1 = tem;
      tem = op0;
      op0 = op1;
      op1 = tem;
      *op0_ptr = op0;
      *op1_ptr = op1;
      unsignedp0 = unsignedp1;
      unsignedp1 = temi;
      temi = real1;
      real1 = real2;
      real2 = temi;

      switch (code)
	{
	case LT_EXPR:
	  code = GT_EXPR;
	  break;
	case GT_EXPR:
	  code = LT_EXPR;
	  break;
	case LE_EXPR:
	  code = GE_EXPR;
	  break;
	case GE_EXPR:
	  code = LE_EXPR;
	  break;
	default:
	  break;
	}
      *rescode_ptr = code;
    }

  /* If comparing an integer against a constant more bits wide,
     maybe we can deduce a value of 1 or 0 independent of the data.
     Or else truncate the constant now
     rather than extend the variable at run time.

     This is only interesting if the constant is the wider arg.
     Also, it is not safe if the constant is unsigned and the
     variable arg is signed, since in this case the variable
     would be sign-extended and then regarded as unsigned.
     Our technique fails in this case because the lowest/highest
     possible unsigned results don't follow naturally from the
     lowest/highest possible values of the variable operand.
     For just EQ_EXPR and NE_EXPR there is another technique that
     could be used: see if the constant can be faithfully represented
     in the other operand's type, by truncating it and reextending it
     and see if that preserves the constant's value.  */

  if (!real1 && !real2
      && TREE_CODE (primop1) == INTEGER_CST
      && TYPE_PRECISION (TREE_TYPE (primop0)) < TYPE_PRECISION (*restype_ptr))
    {
      int min_gt, max_gt, min_lt, max_lt;
      tree maxval, minval;
      /* 1 if comparison is nominally unsigned.  */
      int unsignedp = TYPE_UNSIGNED (*restype_ptr);
      tree val;

      type = c_common_signed_or_unsigned_type (unsignedp0,
					       TREE_TYPE (primop0));

      maxval = TYPE_MAX_VALUE (type);
      minval = TYPE_MIN_VALUE (type);

      if (unsignedp && !unsignedp0)
	*restype_ptr = c_common_signed_type (*restype_ptr);

      if (TREE_TYPE (primop1) != *restype_ptr)
	{
	  /* Convert primop1 to target type, but do not introduce
	     additional overflow.  We know primop1 is an int_cst.  */
	  tree tmp = build_int_cst_wide (*restype_ptr,
					 TREE_INT_CST_LOW (primop1),
					 TREE_INT_CST_HIGH (primop1));

	  primop1 = force_fit_type (tmp, 0, TREE_OVERFLOW (primop1),
				    TREE_CONSTANT_OVERFLOW (primop1));
	}
      if (type != *restype_ptr)
	{
	  minval = convert (*restype_ptr, minval);
	  maxval = convert (*restype_ptr, maxval);
	}

      if (unsignedp && unsignedp0)
	{
	  min_gt = INT_CST_LT_UNSIGNED (primop1, minval);
	  max_gt = INT_CST_LT_UNSIGNED (primop1, maxval);
	  min_lt = INT_CST_LT_UNSIGNED (minval, primop1);
	  max_lt = INT_CST_LT_UNSIGNED (maxval, primop1);
	}
      else
	{
	  min_gt = INT_CST_LT (primop1, minval);
	  max_gt = INT_CST_LT (primop1, maxval);
	  min_lt = INT_CST_LT (minval, primop1);
	  max_lt = INT_CST_LT (maxval, primop1);
	}

      val = 0;
      /* This used to be a switch, but Genix compiler can't handle that.  */
      if (code == NE_EXPR)
	{
	  if (max_lt || min_gt)
	    val = truthvalue_true_node;
	}
      else if (code == EQ_EXPR)
	{
	  if (max_lt || min_gt)
	    val = truthvalue_false_node;
	}
      else if (code == LT_EXPR)
	{
	  if (max_lt)
	    val = truthvalue_true_node;
	  if (!min_lt)
	    val = truthvalue_false_node;
	}
      else if (code == GT_EXPR)
	{
	  if (min_gt)
	    val = truthvalue_true_node;
	  if (!max_gt)
	    val = truthvalue_false_node;
	}
      else if (code == LE_EXPR)
	{
	  if (!max_gt)
	    val = truthvalue_true_node;
	  if (min_gt)
	    val = truthvalue_false_node;
	}
      else if (code == GE_EXPR)
	{
	  if (!min_lt)
	    val = truthvalue_true_node;
	  if (max_lt)
	    val = truthvalue_false_node;
	}

      /* If primop0 was sign-extended and unsigned comparison specd,
	 we did a signed comparison above using the signed type bounds.
	 But the comparison we output must be unsigned.

	 Also, for inequalities, VAL is no good; but if the signed
	 comparison had *any* fixed result, it follows that the
	 unsigned comparison just tests the sign in reverse
	 (positive values are LE, negative ones GE).
	 So we can generate an unsigned comparison
	 against an extreme value of the signed type.  */

      if (unsignedp && !unsignedp0)
	{
	  if (val != 0)
	    switch (code)
	      {
	      case LT_EXPR:
	      case GE_EXPR:
		primop1 = TYPE_MIN_VALUE (type);
		val = 0;
		break;

	      case LE_EXPR:
	      case GT_EXPR:
		primop1 = TYPE_MAX_VALUE (type);
		val = 0;
		break;

	      default:
		break;
	      }
	  type = c_common_unsigned_type (type);
	}

      if (TREE_CODE (primop0) != INTEGER_CST)
	{
	  if (val == truthvalue_false_node)
	    warning (0, "comparison is always false due to limited range of data type");
	  if (val == truthvalue_true_node)
	    warning (0, "comparison is always true due to limited range of data type");
	}

      if (val != 0)
	{
	  /* Don't forget to evaluate PRIMOP0 if it has side effects.  */
	  if (TREE_SIDE_EFFECTS (primop0))
	    return build2 (COMPOUND_EXPR, TREE_TYPE (val), primop0, val);
	  return val;
	}

      /* Value is not predetermined, but do the comparison
	 in the type of the operand that is not constant.
	 TYPE is already properly set.  */
    }

  /* If either arg is decimal float and the other is float, find the
     proper common type to use for comparison.  */
  else if (real1 && real2
	   && (DECIMAL_FLOAT_MODE_P (TYPE_MODE (TREE_TYPE (primop0)))
	       || DECIMAL_FLOAT_MODE_P (TYPE_MODE (TREE_TYPE (primop1)))))
    type = common_type (TREE_TYPE (primop0), TREE_TYPE (primop1));

  else if (real1 && real2
	   && (TYPE_PRECISION (TREE_TYPE (primop0))
	       == TYPE_PRECISION (TREE_TYPE (primop1))))
    type = TREE_TYPE (primop0);

  /* If args' natural types are both narrower than nominal type
     and both extend in the same manner, compare them
     in the type of the wider arg.
     Otherwise must actually extend both to the nominal
     common type lest different ways of extending
     alter the result.
     (eg, (short)-1 == (unsigned short)-1  should be 0.)  */

  else if (unsignedp0 == unsignedp1 && real1 == real2
	   && TYPE_PRECISION (TREE_TYPE (primop0)) < TYPE_PRECISION (*restype_ptr)
	   && TYPE_PRECISION (TREE_TYPE (primop1)) < TYPE_PRECISION (*restype_ptr))
    {
      type = common_type (TREE_TYPE (primop0), TREE_TYPE (primop1));
      type = c_common_signed_or_unsigned_type (unsignedp0
					       || TYPE_UNSIGNED (*restype_ptr),
					       type);
      /* Make sure shorter operand is extended the right way
	 to match the longer operand.  */
      primop0
	= convert (c_common_signed_or_unsigned_type (unsignedp0,
						     TREE_TYPE (primop0)),
		   primop0);
      primop1
	= convert (c_common_signed_or_unsigned_type (unsignedp1,
						     TREE_TYPE (primop1)),
		   primop1);
    }
  else
    {
      /* Here we must do the comparison on the nominal type
	 using the args exactly as we received them.  */
      type = *restype_ptr;
      primop0 = op0;
      primop1 = op1;

      if (!real1 && !real2 && integer_zerop (primop1)
	  && TYPE_UNSIGNED (*restype_ptr))
	{
	  tree value = 0;
	  switch (code)
	    {
	    case GE_EXPR:
	      /* All unsigned values are >= 0, so we warn if extra warnings
		 are requested.  However, if OP0 is a constant that is
		 >= 0, the signedness of the comparison isn't an issue,
		 so suppress the warning.  */
	      if (extra_warnings && !in_system_header
		  && !(TREE_CODE (primop0) == INTEGER_CST
		       && !TREE_OVERFLOW (convert (c_common_signed_type (type),
						   primop0))))
		warning (0, "comparison of unsigned expression >= 0 is always true");
	      value = truthvalue_true_node;
	      break;

	    case LT_EXPR:
	      if (extra_warnings && !in_system_header
		  && !(TREE_CODE (primop0) == INTEGER_CST
		       && !TREE_OVERFLOW (convert (c_common_signed_type (type),
						   primop0))))
		warning (0, "comparison of unsigned expression < 0 is always false");
	      value = truthvalue_false_node;
	      break;

	    default:
	      break;
	    }

	  if (value != 0)
	    {
	      /* Don't forget to evaluate PRIMOP0 if it has side effects.  */
	      if (TREE_SIDE_EFFECTS (primop0))
		return build2 (COMPOUND_EXPR, TREE_TYPE (value),
			       primop0, value);
	      return value;
	    }
	}
    }

  *op0_ptr = convert (type, primop0);
  *op1_ptr = convert (type, primop1);

  *restype_ptr = truthvalue_type_node;

  return 0;
}