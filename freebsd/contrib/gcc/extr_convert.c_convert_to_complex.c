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
#define  BOOLEAN_TYPE 134 
 int COMPLEX_EXPR ; 
#define  COMPLEX_TYPE 133 
#define  ENUMERAL_TYPE 132 
 int /*<<< orphan*/  IMAGPART_EXPR ; 
#define  INTEGER_TYPE 131 
#define  POINTER_TYPE 130 
 int /*<<< orphan*/  REALPART_EXPR ; 
#define  REAL_TYPE 129 
#define  REFERENCE_TYPE 128 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  convert (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fold_build1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fold_build2 (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_zero_node ; 
 int /*<<< orphan*/  save_expr (int /*<<< orphan*/ ) ; 

tree
convert_to_complex (tree type, tree expr)
{
  tree subtype = TREE_TYPE (type);

  switch (TREE_CODE (TREE_TYPE (expr)))
    {
    case REAL_TYPE:
    case INTEGER_TYPE:
    case ENUMERAL_TYPE:
    case BOOLEAN_TYPE:
      return build2 (COMPLEX_EXPR, type, convert (subtype, expr),
		     convert (subtype, integer_zero_node));

    case COMPLEX_TYPE:
      {
	tree elt_type = TREE_TYPE (TREE_TYPE (expr));

	if (TYPE_MAIN_VARIANT (elt_type) == TYPE_MAIN_VARIANT (subtype))
	  return expr;
	else if (TREE_CODE (expr) == COMPLEX_EXPR)
	  return fold_build2 (COMPLEX_EXPR, type,
			      convert (subtype, TREE_OPERAND (expr, 0)),
			      convert (subtype, TREE_OPERAND (expr, 1)));
	else
	  {
	    expr = save_expr (expr);
	    return
	      fold_build2 (COMPLEX_EXPR, type,
			   convert (subtype,
				    fold_build1 (REALPART_EXPR,
						 TREE_TYPE (TREE_TYPE (expr)),
						 expr)),
			   convert (subtype,
				    fold_build1 (IMAGPART_EXPR,
						 TREE_TYPE (TREE_TYPE (expr)),
						 expr)));
	  }
      }

    case POINTER_TYPE:
    case REFERENCE_TYPE:
      error ("pointer value used where a complex was expected");
      return convert_to_complex (type, integer_zero_node);

    default:
      error ("aggregate value used where a complex was expected");
      return convert_to_complex (type, integer_zero_node);
    }
}