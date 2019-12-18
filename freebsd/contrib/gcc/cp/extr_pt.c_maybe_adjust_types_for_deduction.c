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
typedef  int unification_kind_t ;
typedef  int /*<<< orphan*/  tree ;

/* Variables and functions */
 scalar_t__ ARRAY_TYPE ; 
#define  DEDUCE_CALL 130 
#define  DEDUCE_CONV 129 
#define  DEDUCE_EXACT 128 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ REFERENCE_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int UNIFY_ALLOW_OUTER_MORE_CV_QUAL ; 
 int /*<<< orphan*/  build_pointer_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
maybe_adjust_types_for_deduction (unification_kind_t strict,
				  tree* parm,
				  tree* arg)
{
  int result = 0;

  switch (strict)
    {
    case DEDUCE_CALL:
      break;

    case DEDUCE_CONV:
      {
	/* Swap PARM and ARG throughout the remainder of this
	   function; the handling is precisely symmetric since PARM
	   will initialize ARG rather than vice versa.  */
	tree* temp = parm;
	parm = arg;
	arg = temp;
	break;
      }

    case DEDUCE_EXACT:
      /* There is nothing to do in this case.  */
      return 0;

    default:
      gcc_unreachable ();
    }

  if (TREE_CODE (*parm) != REFERENCE_TYPE)
    {
      /* [temp.deduct.call]

	 If P is not a reference type:

	 --If A is an array type, the pointer type produced by the
	 array-to-pointer standard conversion (_conv.array_) is
	 used in place of A for type deduction; otherwise,

	 --If A is a function type, the pointer type produced by
	 the function-to-pointer standard conversion
	 (_conv.func_) is used in place of A for type deduction;
	 otherwise,

	 --If A is a cv-qualified type, the top level
	 cv-qualifiers of A's type are ignored for type
	 deduction.  */
      if (TREE_CODE (*arg) == ARRAY_TYPE)
	*arg = build_pointer_type (TREE_TYPE (*arg));
      else if (TREE_CODE (*arg) == FUNCTION_TYPE)
	*arg = build_pointer_type (*arg);
      else
	*arg = TYPE_MAIN_VARIANT (*arg);
    }

  /* [temp.deduct.call]

     If P is a cv-qualified type, the top level cv-qualifiers
     of P's type are ignored for type deduction.  If P is a
     reference type, the type referred to by P is used for
     type deduction.  */
  *parm = TYPE_MAIN_VARIANT (*parm);
  if (TREE_CODE (*parm) == REFERENCE_TYPE)
    {
      *parm = TREE_TYPE (*parm);
      result |= UNIFY_ALLOW_OUTER_MORE_CV_QUAL;
    }

  /* DR 322. For conversion deduction, remove a reference type on parm
     too (which has been swapped into ARG).  */
  if (strict == DEDUCE_CONV && TREE_CODE (*arg) == REFERENCE_TYPE)
    *arg = TREE_TYPE (*arg);

  return result;
}