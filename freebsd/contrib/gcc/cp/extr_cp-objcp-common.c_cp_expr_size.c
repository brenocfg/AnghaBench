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
 int /*<<< orphan*/  CLASSTYPE_SIZE_UNIT (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ CONSTRUCTOR ; 
 scalar_t__ CP_AGGREGATE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_HAS_COMPLEX_ASSIGN_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_HAS_COMPLEX_INIT_REF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ is_empty_class (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lhd_expr_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  size_zero_node ; 

tree
cp_expr_size (tree exp)
{
  tree type = TREE_TYPE (exp);

  if (CLASS_TYPE_P (type))
    {
      /* The backend should not be interested in the size of an expression
	 of a type with both of these set; all copies of such types must go
	 through a constructor or assignment op.  */
      gcc_assert (!TYPE_HAS_COMPLEX_INIT_REF (type)
		  || !TYPE_HAS_COMPLEX_ASSIGN_REF (type)
		  /* But storing a CONSTRUCTOR isn't a copy.  */
		  || TREE_CODE (exp) == CONSTRUCTOR
		  /* And, the gimplifier will sometimes make a copy of
		     an aggregate.  In particular, for a case like:

			struct S { S(); };
			struct X { int a; S s; };
			X x = { 0 };

		     the gimplifier will create a temporary with
		     static storage duration, perform static
		     initialization of the temporary, and then copy
		     the result.  Since the "s" subobject is never
		     constructed, this is a valid transformation.  */
		  || CP_AGGREGATE_TYPE_P (type));

      /* This would be wrong for a type with virtual bases, but they are
	 caught by the assert above.  */
      return (is_empty_class (type)
	      ? size_zero_node
	      : CLASSTYPE_SIZE_UNIT (type));
    }
  else
    /* Use the default code.  */
    return lhd_expr_size (exp);
}