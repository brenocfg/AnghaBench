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
typedef  int /*<<< orphan*/  c_pretty_printer ;

/* Variables and functions */
#define  ARRAY_TYPE 142 
#define  BLOCK_POINTER_TYPE 141 
#define  BOOLEAN_TYPE 140 
#define  COMPLEX_TYPE 139 
#define  ENUMERAL_TYPE 138 
#define  FUNCTION_TYPE 137 
#define  IDENTIFIER_NODE 136 
#define  INTEGER_TYPE 135 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  POINTER_TYPE 134 
#define  REAL_TYPE 133 
#define  RECORD_TYPE 132 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 131 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  build2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  build_int_cst (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_left_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_parameter_type_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_right_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_direct_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_wide_integer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
pp_c_direct_abstract_declarator (c_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
    /* APPLE LOCAL blocks */
    case BLOCK_POINTER_TYPE:
      pp_abstract_declarator (pp, t);
      break;

    case FUNCTION_TYPE:
      pp_c_parameter_type_list (pp, t);
      pp_direct_abstract_declarator (pp, TREE_TYPE (t));
      break;

    case ARRAY_TYPE:
      pp_c_left_bracket (pp);
      if (TYPE_DOMAIN (t) && TYPE_MAX_VALUE (TYPE_DOMAIN (t)))
	{
	  tree maxval = TYPE_MAX_VALUE (TYPE_DOMAIN (t));
	  tree type = TREE_TYPE (maxval);

	  if (host_integerp (maxval, 0))
	    pp_wide_integer (pp, tree_low_cst (maxval, 0) + 1);
	  else
	    pp_expression (pp, fold (build2 (PLUS_EXPR, type, maxval,
					     build_int_cst (type, 1))));
	}
      pp_c_right_bracket (pp);
      pp_direct_abstract_declarator (pp, TREE_TYPE (t));
      break;

    case IDENTIFIER_NODE:
    case VOID_TYPE:
    case BOOLEAN_TYPE:
    case INTEGER_TYPE:
    case REAL_TYPE:
    case ENUMERAL_TYPE:
    case RECORD_TYPE:
    case UNION_TYPE:
    case VECTOR_TYPE:
    case COMPLEX_TYPE:
    case TYPE_DECL:
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}