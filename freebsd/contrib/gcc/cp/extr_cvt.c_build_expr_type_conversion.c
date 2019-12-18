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

/* Variables and functions */
#define  ARRAY_TYPE 135 
#define  BOOLEAN_TYPE 134 
#define  ENUMERAL_TYPE 133 
#define  FUNCTION_TYPE 132 
#define  INTEGER_TYPE 131 
 int /*<<< orphan*/  IS_AGGR_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  LOOKUP_NORMAL ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  OPT_Wconversion ; 
#define  POINTER_TYPE 130 
#define  REAL_TYPE 129 
 scalar_t__ TREE_CHAIN (scalar_t__) ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 scalar_t__ TREE_VALUE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_HAS_CONVERSION (scalar_t__) ; 
#define  VECTOR_TYPE 128 
 int WANT_ENUM ; 
 int WANT_FLOAT ; 
 int WANT_INT ; 
 int WANT_NULL ; 
 int WANT_POINTER ; 
 int WANT_VECTOR ; 
 scalar_t__ build_user_type_conversion (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  complete_type_or_else (scalar_t__,scalar_t__) ; 
 scalar_t__ decay_conversion (scalar_t__) ; 
 int /*<<< orphan*/  error (char*,scalar_t__,...) ; 
 scalar_t__ error_mark_node ; 
 scalar_t__ lookup_conversions (scalar_t__) ; 
 scalar_t__ non_reference (scalar_t__) ; 
 scalar_t__ null_node ; 
 int /*<<< orphan*/  null_ptr_cst_p (scalar_t__) ; 
 int /*<<< orphan*/  warning (int /*<<< orphan*/ ,char*) ; 

tree
build_expr_type_conversion (int desires, tree expr, bool complain)
{
  tree basetype = TREE_TYPE (expr);
  tree conv = NULL_TREE;
  tree winner = NULL_TREE;

  if (expr == null_node
      && (desires & WANT_INT)
      && !(desires & WANT_NULL))
    warning (OPT_Wconversion, "converting NULL to non-pointer type");

  basetype = TREE_TYPE (expr);

  if (basetype == error_mark_node)
    return error_mark_node;

  if (! IS_AGGR_TYPE (basetype))
    switch (TREE_CODE (basetype))
      {
      case INTEGER_TYPE:
	if ((desires & WANT_NULL) && null_ptr_cst_p (expr))
	  return expr;
	/* else fall through...  */

      case BOOLEAN_TYPE:
	return (desires & WANT_INT) ? expr : NULL_TREE;
      case ENUMERAL_TYPE:
	return (desires & WANT_ENUM) ? expr : NULL_TREE;
      case REAL_TYPE:
	return (desires & WANT_FLOAT) ? expr : NULL_TREE;
      case POINTER_TYPE:
	return (desires & WANT_POINTER) ? expr : NULL_TREE;

      case FUNCTION_TYPE:
      case ARRAY_TYPE:
	return (desires & WANT_POINTER) ? decay_conversion (expr)
					: NULL_TREE;

      case VECTOR_TYPE:
	if ((desires & WANT_VECTOR) == 0)
	  return NULL_TREE;
	switch (TREE_CODE (TREE_TYPE (basetype)))
	  {
	  case INTEGER_TYPE:
	  case BOOLEAN_TYPE:
	    return (desires & WANT_INT) ? expr : NULL_TREE;
	  case ENUMERAL_TYPE:
	    return (desires & WANT_ENUM) ? expr : NULL_TREE;
	  case REAL_TYPE:
	    return (desires & WANT_FLOAT) ? expr : NULL_TREE;
	  default:
	    return NULL_TREE;
	  }

      default:
	return NULL_TREE;
      }

  /* The code for conversions from class type is currently only used for
     delete expressions.  Other expressions are handled by build_new_op.  */
  if (!complete_type_or_else (basetype, expr))
    return error_mark_node;
  if (!TYPE_HAS_CONVERSION (basetype))
    return NULL_TREE;

  for (conv = lookup_conversions (basetype); conv; conv = TREE_CHAIN (conv))
    {
      int win = 0;
      tree candidate;
      tree cand = TREE_VALUE (conv);

      if (winner && winner == cand)
	continue;

      candidate = non_reference (TREE_TYPE (TREE_TYPE (cand)));

      switch (TREE_CODE (candidate))
	{
	case BOOLEAN_TYPE:
	case INTEGER_TYPE:
	  win = (desires & WANT_INT); break;
	case ENUMERAL_TYPE:
	  win = (desires & WANT_ENUM); break;
	case REAL_TYPE:
	  win = (desires & WANT_FLOAT); break;
	case POINTER_TYPE:
	  win = (desires & WANT_POINTER); break;

	case VECTOR_TYPE:
	  if ((desires & WANT_VECTOR) == 0)
	    break;
	  switch (TREE_CODE (TREE_TYPE (candidate)))
	    {
	    case BOOLEAN_TYPE:
	    case INTEGER_TYPE:
	      win = (desires & WANT_INT); break;
	    case ENUMERAL_TYPE:
	      win = (desires & WANT_ENUM); break;
	    case REAL_TYPE:
	      win = (desires & WANT_FLOAT); break;
	    default:
	      break;
	    }
	  break;

	default:
	  break;
	}

      if (win)
	{
	  if (winner)
	    {
	      if (complain)
		{
		  error ("ambiguous default type conversion from %qT",
			 basetype);
		  error ("  candidate conversions include %qD and %qD",
			 winner, cand);
		}
	      return error_mark_node;
	    }
	  else
	    winner = cand;
	}
    }

  if (winner)
    {
      tree type = non_reference (TREE_TYPE (TREE_TYPE (winner)));
      return build_user_type_conversion (type, expr, LOOKUP_NORMAL);
    }

  return NULL_TREE;
}