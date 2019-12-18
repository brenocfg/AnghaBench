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

/* Variables and functions */
#define  ARRAY_TYPE 129 
 scalar_t__ DECL_CONV_FN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_INNERMOST_TEMPLATE_PARMS (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NTPARMS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_STATIC_FUNCTION_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_TEMPLATE_RESULT (int /*<<< orphan*/ ) ; 
#define  FUNCTION_TYPE 128 
 int /*<<< orphan*/  NULL_TREE ; 
 int REFERENCE_TYPE ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIFY_ALLOW_NONE ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int cp_type_quals (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_tree_vec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 int /*<<< orphan*/  tree_cons (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unify (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
more_specialized_fn (tree pat1, tree pat2, int len)
{
  tree decl1 = DECL_TEMPLATE_RESULT (pat1);
  tree decl2 = DECL_TEMPLATE_RESULT (pat2);
  tree targs1 = make_tree_vec (DECL_NTPARMS (pat1));
  tree targs2 = make_tree_vec (DECL_NTPARMS (pat2));
  tree tparms1 = DECL_INNERMOST_TEMPLATE_PARMS (pat1);
  tree tparms2 = DECL_INNERMOST_TEMPLATE_PARMS (pat2);
  tree args1 = TYPE_ARG_TYPES (TREE_TYPE (decl1));
  tree args2 = TYPE_ARG_TYPES (TREE_TYPE (decl2));
  int better1 = 0;
  int better2 = 0;

  /* Remove the this parameter from non-static member functions.  If
     one is a non-static member function and the other is not a static
     member function, remove the first parameter from that function
     also.  This situation occurs for operator functions where we
     locate both a member function (with this pointer) and non-member
     operator (with explicit first operand).  */
  if (DECL_NONSTATIC_MEMBER_FUNCTION_P (decl1))
    {
      len--; /* LEN is the number of significant arguments for DECL1 */
      args1 = TREE_CHAIN (args1);
      if (!DECL_STATIC_FUNCTION_P (decl2))
	args2 = TREE_CHAIN (args2);
    }
  else if (DECL_NONSTATIC_MEMBER_FUNCTION_P (decl2))
    {
      args2 = TREE_CHAIN (args2);
      if (!DECL_STATIC_FUNCTION_P (decl1))
	{
	  len--;
	  args1 = TREE_CHAIN (args1);
	}
    }

  /* If only one is a conversion operator, they are unordered.  */
  if (DECL_CONV_FN_P (decl1) != DECL_CONV_FN_P (decl2))
    return 0;

  /* Consider the return type for a conversion function */
  if (DECL_CONV_FN_P (decl1))
    {
      args1 = tree_cons (NULL_TREE, TREE_TYPE (TREE_TYPE (decl1)), args1);
      args2 = tree_cons (NULL_TREE, TREE_TYPE (TREE_TYPE (decl2)), args2);
      len++;
    }

  processing_template_decl++;

  while (len--)
    {
      tree arg1 = TREE_VALUE (args1);
      tree arg2 = TREE_VALUE (args2);
      int deduce1, deduce2;
      int quals1 = -1;
      int quals2 = -1;

      if (TREE_CODE (arg1) == REFERENCE_TYPE)
	{
	  arg1 = TREE_TYPE (arg1);
	  quals1 = cp_type_quals (arg1);
	}

      if (TREE_CODE (arg2) == REFERENCE_TYPE)
	{
	  arg2 = TREE_TYPE (arg2);
	  quals2 = cp_type_quals (arg2);
	}

      if ((quals1 < 0) != (quals2 < 0))
	{
	  /* Only of the args is a reference, see if we should apply
	     array/function pointer decay to it.  This is not part of
	     DR214, but is, IMHO, consistent with the deduction rules
	     for the function call itself, and with our earlier
	     implementation of the underspecified partial ordering
	     rules.  (nathan).  */
	  if (quals1 >= 0)
	    {
	      switch (TREE_CODE (arg1))
		{
		case ARRAY_TYPE:
		  arg1 = TREE_TYPE (arg1);
		  /* FALLTHROUGH. */
		case FUNCTION_TYPE:
		  arg1 = build_pointer_type (arg1);
		  break;

		default:
		  break;
		}
	    }
	  else
	    {
	      switch (TREE_CODE (arg2))
		{
		case ARRAY_TYPE:
		  arg2 = TREE_TYPE (arg2);
		  /* FALLTHROUGH. */
		case FUNCTION_TYPE:
		  arg2 = build_pointer_type (arg2);
		  break;

		default:
		  break;
		}
	    }
	}

      arg1 = TYPE_MAIN_VARIANT (arg1);
      arg2 = TYPE_MAIN_VARIANT (arg2);

      deduce1 = !unify (tparms1, targs1, arg1, arg2, UNIFY_ALLOW_NONE);
      deduce2 = !unify (tparms2, targs2, arg2, arg1, UNIFY_ALLOW_NONE);

      if (!deduce1)
	better2 = -1;
      if (!deduce2)
	better1 = -1;
      if (better1 < 0 && better2 < 0)
	/* We've failed to deduce something in either direction.
	   These must be unordered.  */
	break;

      if (deduce1 && deduce2 && quals1 >= 0 && quals2 >= 0)
	{
	  /* Deduces in both directions, see if quals can
	     disambiguate.  Pretend the worse one failed to deduce. */
	  if ((quals1 & quals2) == quals2)
	    deduce1 = 0;
	  if ((quals1 & quals2) == quals1)
	    deduce2 = 0;
	}
      if (deduce1 && !deduce2 && !better2)
	better2 = 1;
      if (deduce2 && !deduce1 && !better1)
	better1 = 1;

      args1 = TREE_CHAIN (args1);
      args2 = TREE_CHAIN (args2);
    }

  processing_template_decl--;

  return (better1 > 0) - (better2 > 0);
}