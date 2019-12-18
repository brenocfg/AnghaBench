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
struct TYPE_2__ {scalar_t__ (* types_compatible_p ) (scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
#define  BLOCK_POINTER_TYPE 138 
#define  BOOLEAN_TYPE 137 
 int const COMPLEX_EXPR ; 
#define  COMPLEX_TYPE 136 
#define  ENUMERAL_TYPE 135 
 scalar_t__ ERROR_MARK ; 
 int /*<<< orphan*/  FLOAT_EXPR ; 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
 int const INTEGER_CST ; 
#define  INTEGER_TYPE 134 
 int /*<<< orphan*/  INTEGRAL_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  NOP_EXPR ; 
 scalar_t__ NULL_TREE ; 
#define  OFFSET_TYPE 133 
#define  POINTER_TYPE 132 
 int /*<<< orphan*/  POINTER_TYPE_P (scalar_t__) ; 
 int /*<<< orphan*/  REALPART_EXPR ; 
 int const REAL_CST ; 
#define  REAL_TYPE 131 
#define  REFERENCE_TYPE 130 
 int const TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TYPE_MAIN_VARIANT (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_SIZE (scalar_t__) ; 
#define  VECTOR_TYPE 129 
 int /*<<< orphan*/  VIEW_CONVERT_EXPR ; 
#define  VOID_TYPE 128 
 scalar_t__ build2 (int const,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ build_zero_vector (scalar_t__) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ fold_build1 (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_build2 (int const,scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_convert_const (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ fold_ignored_result (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ integer_zero_node ; 
 int /*<<< orphan*/  integer_zerop (scalar_t__) ; 
 TYPE_1__ lang_hooks ; 
 scalar_t__ save_expr (scalar_t__) ; 
 scalar_t__ stub1 (scalar_t__,scalar_t__) ; 
 int tree_int_cst_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

tree
fold_convert (tree type, tree arg)
{
  tree orig = TREE_TYPE (arg);
  tree tem;

  if (type == orig)
    return arg;

  if (TREE_CODE (arg) == ERROR_MARK
      || TREE_CODE (type) == ERROR_MARK
      || TREE_CODE (orig) == ERROR_MARK)
    return error_mark_node;

  if (TYPE_MAIN_VARIANT (type) == TYPE_MAIN_VARIANT (orig)
      || lang_hooks.types_compatible_p (TYPE_MAIN_VARIANT (type),
					TYPE_MAIN_VARIANT (orig)))
    return fold_build1 (NOP_EXPR, type, arg);

  switch (TREE_CODE (type))
    {
    case INTEGER_TYPE: case ENUMERAL_TYPE: case BOOLEAN_TYPE:
    case POINTER_TYPE: case REFERENCE_TYPE:
      /* APPLE LOCAL blocks 5862465 */
    case BLOCK_POINTER_TYPE:
    case OFFSET_TYPE:
      if (TREE_CODE (arg) == INTEGER_CST)
	{
	  tem = fold_convert_const (NOP_EXPR, type, arg);
	  if (tem != NULL_TREE)
	    return tem;
	}
      if (INTEGRAL_TYPE_P (orig) || POINTER_TYPE_P (orig)
	  || TREE_CODE (orig) == OFFSET_TYPE)
        return fold_build1 (NOP_EXPR, type, arg);
      if (TREE_CODE (orig) == COMPLEX_TYPE)
	{
	  tem = fold_build1 (REALPART_EXPR, TREE_TYPE (orig), arg);
	  return fold_convert (type, tem);
	}
      gcc_assert (TREE_CODE (orig) == VECTOR_TYPE
		  && tree_int_cst_equal (TYPE_SIZE (type), TYPE_SIZE (orig)));
      return fold_build1 (NOP_EXPR, type, arg);

    case REAL_TYPE:
      if (TREE_CODE (arg) == INTEGER_CST)
	{
	  tem = fold_convert_const (FLOAT_EXPR, type, arg);
	  if (tem != NULL_TREE)
	    return tem;
	}
      else if (TREE_CODE (arg) == REAL_CST)
	{
	  tem = fold_convert_const (NOP_EXPR, type, arg);
	  if (tem != NULL_TREE)
	    return tem;
	}

      switch (TREE_CODE (orig))
	{
	case INTEGER_TYPE:
	case BOOLEAN_TYPE: case ENUMERAL_TYPE:
	case POINTER_TYPE: case REFERENCE_TYPE:
	  return fold_build1 (FLOAT_EXPR, type, arg);

	case REAL_TYPE:
	  return fold_build1 (NOP_EXPR, type, arg);

	case COMPLEX_TYPE:
	  tem = fold_build1 (REALPART_EXPR, TREE_TYPE (orig), arg);
	  return fold_convert (type, tem);

	default:
	  gcc_unreachable ();
	}

    case COMPLEX_TYPE:
      switch (TREE_CODE (orig))
	{
	case INTEGER_TYPE:
	case BOOLEAN_TYPE: case ENUMERAL_TYPE:
	case POINTER_TYPE: case REFERENCE_TYPE:
	case REAL_TYPE:
	  return build2 (COMPLEX_EXPR, type,
			 fold_convert (TREE_TYPE (type), arg),
			 fold_convert (TREE_TYPE (type), integer_zero_node));
	case COMPLEX_TYPE:
	  {
	    tree rpart, ipart;

	    if (TREE_CODE (arg) == COMPLEX_EXPR)
	      {
		rpart = fold_convert (TREE_TYPE (type), TREE_OPERAND (arg, 0));
		ipart = fold_convert (TREE_TYPE (type), TREE_OPERAND (arg, 1));
		return fold_build2 (COMPLEX_EXPR, type, rpart, ipart);
	      }

	    arg = save_expr (arg);
	    rpart = fold_build1 (REALPART_EXPR, TREE_TYPE (orig), arg);
	    ipart = fold_build1 (IMAGPART_EXPR, TREE_TYPE (orig), arg);
	    rpart = fold_convert (TREE_TYPE (type), rpart);
	    ipart = fold_convert (TREE_TYPE (type), ipart);
	    return fold_build2 (COMPLEX_EXPR, type, rpart, ipart);
	  }

	default:
	  gcc_unreachable ();
	}

    case VECTOR_TYPE:
      if (integer_zerop (arg))
	return build_zero_vector (type);
      gcc_assert (tree_int_cst_equal (TYPE_SIZE (type), TYPE_SIZE (orig)));
      gcc_assert (INTEGRAL_TYPE_P (orig) || POINTER_TYPE_P (orig)
		  || TREE_CODE (orig) == VECTOR_TYPE);
      return fold_build1 (VIEW_CONVERT_EXPR, type, arg);

    case VOID_TYPE:
      return fold_build1 (NOP_EXPR, type, fold_ignored_result (arg));

    default:
      gcc_unreachable ();
    }
}