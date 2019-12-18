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
#define  ARRAY_TYPE 154 
#define  BLOCK_POINTER_TYPE 153 
#define  BOOLEAN_TYPE 152 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 151 
#define  COMPLEX_TYPE 150 
#define  ENUMERAL_TYPE 149 
#define  ERROR_MARK 148 
#define  FUNCTION_TYPE 147 
#define  IDENTIFIER_NODE 146 
#define  INTEGER_TYPE 145 
#define  METHOD_TYPE 144 
 int const MINUS_EXPR ; 
#define  OFFSET_TYPE 143 
 int /*<<< orphan*/  PLUS_EXPR ; 
#define  POINTER_TYPE 142 
#define  REAL_TYPE 141 
#define  RECORD_TYPE 140 
#define  REFERENCE_TYPE 139 
#define  TEMPLATE_TEMPLATE_PARM 138 
#define  TEMPLATE_TYPE_PARM 137 
 int TFF_EXPR_IN_PARENS ; 
 int TFF_FUNCTION_DEFAULT_ARGUMENTS ; 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TREE_LIST 136 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
#define  TREE_VEC 135 
#define  TYPENAME_TYPE 134 
#define  TYPEOF_TYPE 133 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 132 
 int /*<<< orphan*/  TYPE_DOMAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_MAX_VALUE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_RAISES_EXCEPTIONS (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 131 
#define  UNKNOWN_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  cp_build_binary_op (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_exception_spec (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_parameters (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  host_integerp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  integer_one_node ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_left_bracket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_bracket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_maybe_space (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_wide_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tree_low_cst (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_type_suffix (tree t, int flags)
{
  if (TYPE_PTRMEMFUNC_P (t))
    t = TYPE_PTRMEMFUNC_FN_TYPE (t);

  switch (TREE_CODE (t))
    {
    case POINTER_TYPE:
      /* APPLE LOCAL blocks 6040305 */
    case BLOCK_POINTER_TYPE:
    case REFERENCE_TYPE:
    case OFFSET_TYPE:
      if (TREE_CODE (TREE_TYPE (t)) == ARRAY_TYPE)
	pp_cxx_right_paren (cxx_pp);
      dump_type_suffix (TREE_TYPE (t), flags);
      break;

      /* Can only be reached through function pointer.  */
    case FUNCTION_TYPE:
    case METHOD_TYPE:
      {
	tree arg;
	pp_cxx_right_paren (cxx_pp);
	arg = TYPE_ARG_TYPES (t);
	if (TREE_CODE (t) == METHOD_TYPE)
	  arg = TREE_CHAIN (arg);

	/* Function pointers don't have default args.  Not in standard C++,
	   anyway; they may in g++, but we'll just pretend otherwise.  */
	dump_parameters (arg, flags & ~TFF_FUNCTION_DEFAULT_ARGUMENTS);

	if (TREE_CODE (t) == METHOD_TYPE)
	  pp_cxx_cv_qualifier_seq
	    (cxx_pp, TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (t))));
	else
	  pp_cxx_cv_qualifier_seq(cxx_pp, t);
	dump_exception_spec (TYPE_RAISES_EXCEPTIONS (t), flags);
	dump_type_suffix (TREE_TYPE (t), flags);
	break;
      }

    case ARRAY_TYPE:
      pp_maybe_space (cxx_pp);
      pp_cxx_left_bracket (cxx_pp);
      if (TYPE_DOMAIN (t))
	{
	  if (host_integerp (TYPE_MAX_VALUE (TYPE_DOMAIN (t)), 0))
	    pp_wide_integer
	      (cxx_pp, tree_low_cst (TYPE_MAX_VALUE (TYPE_DOMAIN (t)), 0) + 1);
	  else if (TREE_CODE (TYPE_MAX_VALUE (TYPE_DOMAIN (t))) == MINUS_EXPR)
	    dump_expr (TREE_OPERAND (TYPE_MAX_VALUE (TYPE_DOMAIN (t)), 0),
		       flags & ~TFF_EXPR_IN_PARENS);
	  else
	    dump_expr (fold (cp_build_binary_op
			     (PLUS_EXPR, TYPE_MAX_VALUE (TYPE_DOMAIN (t)),
			      integer_one_node)),
		       flags & ~TFF_EXPR_IN_PARENS);
	}
      pp_cxx_right_bracket (cxx_pp);
      dump_type_suffix (TREE_TYPE (t), flags);
      break;

    case ENUMERAL_TYPE:
    case IDENTIFIER_NODE:
    case INTEGER_TYPE:
    case BOOLEAN_TYPE:
    case REAL_TYPE:
    case RECORD_TYPE:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case TREE_LIST:
    case TYPE_DECL:
    case TREE_VEC:
    case UNION_TYPE:
    case UNKNOWN_TYPE:
    case VOID_TYPE:
    case TYPENAME_TYPE:
    case COMPLEX_TYPE:
    case VECTOR_TYPE:
    case TYPEOF_TYPE:
      break;

    default:
      pp_unsupported_tree (cxx_pp, t);
    case ERROR_MARK:
      /* Don't mark it here, we should have already done in
	 dump_type_prefix.  */
      break;
    }
}