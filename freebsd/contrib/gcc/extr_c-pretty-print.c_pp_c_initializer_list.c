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
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  ARRAY_TYPE 132 
 int COMPLEX_CST ; 
 int COMPLEX_EXPR ; 
#define  COMPLEX_TYPE 131 
 int CONSTRUCTOR ; 
 int /*<<< orphan*/  CONSTRUCTOR_ELTS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NULL_TREE ; 
#define  RECORD_TYPE 130 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_IMAGPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_PURPOSE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_REALPART (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VECTOR_CST_ELTS (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 129 
 int VECTOR_CST ; 
#define  VECTOR_TYPE 128 
 int /*<<< orphan*/  pp_c_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_constructor_elts (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_dot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_expression_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_left_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_primary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_right_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_whitespace (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_equal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_initializer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_c_initializer_list (c_pretty_printer *pp, tree e)
{
  tree type = TREE_TYPE (e);
  const enum tree_code code = TREE_CODE (type);

  switch (code)
    {
    case RECORD_TYPE:
    case UNION_TYPE:
    case ARRAY_TYPE:
      {
	tree init = TREE_OPERAND (e, 0);
	for (; init != NULL_TREE; init = TREE_CHAIN (init))
	  {
	    if (code == RECORD_TYPE || code == UNION_TYPE)
	      {
		pp_c_dot (pp);
		pp_c_primary_expression (pp, TREE_PURPOSE (init));
	      }
	    else
	      {
		pp_c_left_bracket (pp);
		if (TREE_PURPOSE (init))
		  pp_c_constant (pp, TREE_PURPOSE (init));
		pp_c_right_bracket (pp);
	      }
	    pp_c_whitespace (pp);
	    pp_equal (pp);
	    pp_c_whitespace (pp);
	    pp_initializer (pp, TREE_VALUE (init));
	    if (TREE_CHAIN (init))
	      pp_separate_with (pp, ',');
	  }
      }
      return;

    case VECTOR_TYPE:
      if (TREE_CODE (e) == VECTOR_CST)
	pp_c_expression_list (pp, TREE_VECTOR_CST_ELTS (e));
      else if (TREE_CODE (e) == CONSTRUCTOR)
	pp_c_constructor_elts (pp, CONSTRUCTOR_ELTS (e));
      else
	break;
      return;

    case COMPLEX_TYPE:
      if (TREE_CODE (e) == CONSTRUCTOR)
	pp_c_constructor_elts (pp, CONSTRUCTOR_ELTS (e));
      else if (TREE_CODE (e) == COMPLEX_CST || TREE_CODE (e) == COMPLEX_EXPR)
	{
	  const bool cst = TREE_CODE (e) == COMPLEX_CST;
	  pp_expression (pp, cst ? TREE_REALPART (e) : TREE_OPERAND (e, 0));
	  pp_separate_with (pp, ',');
	  pp_expression (pp, cst ? TREE_IMAGPART (e) : TREE_OPERAND (e, 1));
	}
      else
	break;
      return;

    default:
      break;
    }

  pp_unsupported_tree (pp, type);
}