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
#define  ARRAY_TYPE 157 
 scalar_t__ BINFO_TYPE (scalar_t__) ; 
#define  BLOCK_POINTER_TYPE 156 
#define  BOOLEAN_TYPE 155 
#define  BOUND_TEMPLATE_TEMPLATE_PARM 154 
#define  COMPLEX_TYPE 153 
 scalar_t__ DECL_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ DECL_ORIGINAL_TYPE (scalar_t__) ; 
#define  ENUMERAL_TYPE 152 
#define  ERROR_MARK 151 
#define  FUNCTION_TYPE 150 
#define  IDENTIFIER_NODE 149 
#define  INTEGER_TYPE 148 
#define  METHOD_TYPE 147 
#define  NAMESPACE_DECL 146 
 scalar_t__ NULL_TREE ; 
#define  OFFSET_TYPE 145 
#define  POINTER_TYPE 144 
#define  REAL_TYPE 143 
#define  RECORD_TYPE 142 
#define  REFERENCE_TYPE 141 
#define  TEMPLATE_DECL 140 
#define  TEMPLATE_TEMPLATE_PARM 139 
#define  TEMPLATE_TYPE_PARM 138 
 scalar_t__ TEMPLATE_TYPE_PARM_INDEX (scalar_t__) ; 
 int TFF_CHASE_TYPEDEF ; 
 int TFF_DECL_SPECIFIERS ; 
 int TFF_EXPR_IN_PARENS ; 
#define  TREE_BINFO 137 
 int TREE_CODE (scalar_t__) ; 
#define  TREE_LIST 136 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPENAME_IS_CLASS_P (scalar_t__) ; 
 int /*<<< orphan*/  TYPENAME_IS_ENUM_P (scalar_t__) ; 
#define  TYPENAME_TYPE 135 
#define  TYPEOF_TYPE 134 
 int /*<<< orphan*/  TYPEOF_TYPE_EXPR (scalar_t__) ; 
 scalar_t__ TYPE_CONTEXT (scalar_t__) ; 
#define  TYPE_DECL 133 
 scalar_t__ TYPE_IDENTIFIER (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_NAME (scalar_t__) ; 
 scalar_t__ TYPE_PTRMEMFUNC_P (scalar_t__) ; 
 scalar_t__ TYPE_TI_ARGS (scalar_t__) ; 
#define  UNBOUND_CLASS_TEMPLATE 132 
#define  UNION_TYPE 131 
#define  UNKNOWN_TYPE 130 
#define  VECTOR_TYPE 129 
#define  VOID_TYPE 128 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_aggr_type (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_expr (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_parameters (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_template_argument_list (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_type_prefix (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_type_suffix (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_typename (scalar_t__,int) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_canonical_template_parameter (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_whitespace (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_type_specifier_seq (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
dump_type (tree t, int flags)
{
  if (t == NULL_TREE)
    return;

  if (TYPE_PTRMEMFUNC_P (t))
    goto offset_type;

  switch (TREE_CODE (t))
    {
    case UNKNOWN_TYPE:
      pp_identifier (cxx_pp, "<unresolved overloaded function type>");
      break;

    case TREE_LIST:
      /* A list of function parms.  */
      dump_parameters (t, flags);
      break;

    case IDENTIFIER_NODE:
      pp_cxx_tree_identifier (cxx_pp, t);
      break;

    case TREE_BINFO:
      dump_type (BINFO_TYPE (t), flags);
      break;

    case RECORD_TYPE:
    case UNION_TYPE:
    case ENUMERAL_TYPE:
      dump_aggr_type (t, flags);
      break;

    case TYPE_DECL:
      if (flags & TFF_CHASE_TYPEDEF)
	{
	  dump_type (DECL_ORIGINAL_TYPE (t)
		     ? DECL_ORIGINAL_TYPE (t) : TREE_TYPE (t), flags);
	  break;
	}
      /* Else fall through.  */

    case TEMPLATE_DECL:
    case NAMESPACE_DECL:
      dump_decl (t, flags & ~TFF_DECL_SPECIFIERS);
      break;

    case INTEGER_TYPE:
    case REAL_TYPE:
    case VOID_TYPE:
    case BOOLEAN_TYPE:
    case COMPLEX_TYPE:
    case VECTOR_TYPE:
      pp_type_specifier_seq (cxx_pp, t);
      break;

    case TEMPLATE_TEMPLATE_PARM:
      /* For parameters inside template signature.  */
      if (TYPE_IDENTIFIER (t))
	pp_cxx_tree_identifier (cxx_pp, TYPE_IDENTIFIER (t));
      else
	pp_cxx_canonical_template_parameter (cxx_pp, t);
      break;

    case BOUND_TEMPLATE_TEMPLATE_PARM:
      {
	tree args = TYPE_TI_ARGS (t);
	pp_cxx_cv_qualifier_seq (cxx_pp, t);
	pp_cxx_tree_identifier (cxx_pp, TYPE_IDENTIFIER (t));
	pp_cxx_begin_template_argument_list (cxx_pp);
	dump_template_argument_list (args, flags);
	pp_cxx_end_template_argument_list (cxx_pp);
      }
      break;

    case TEMPLATE_TYPE_PARM:
      pp_cxx_cv_qualifier_seq (cxx_pp, t);
      if (TYPE_IDENTIFIER (t))
	pp_cxx_tree_identifier (cxx_pp, TYPE_IDENTIFIER (t));
      else
	pp_cxx_canonical_template_parameter
	  (cxx_pp, TEMPLATE_TYPE_PARM_INDEX (t));
      break;

      /* This is not always necessary for pointers and such, but doing this
	 reduces code size.  */
    case ARRAY_TYPE:
    case POINTER_TYPE:
      /* APPLE LOCAL blocks 6040305 */
    case BLOCK_POINTER_TYPE:
    case REFERENCE_TYPE:
    case OFFSET_TYPE:
    offset_type:
    case FUNCTION_TYPE:
    case METHOD_TYPE:
    {
      dump_type_prefix (t, flags);
      dump_type_suffix (t, flags);
      break;
    }
    case TYPENAME_TYPE:
      pp_cxx_cv_qualifier_seq (cxx_pp, t);
      pp_cxx_identifier (cxx_pp,
			 TYPENAME_IS_ENUM_P (t) ? "enum"
			 : TYPENAME_IS_CLASS_P (t) ? "class"
			 : "typename");
      dump_typename (t, flags);
      break;

    case UNBOUND_CLASS_TEMPLATE:
      dump_type (TYPE_CONTEXT (t), flags);
      pp_cxx_colon_colon (cxx_pp);
      pp_cxx_identifier (cxx_pp, "template");
      dump_type (DECL_NAME (TYPE_NAME (t)), flags);
      break;

    case TYPEOF_TYPE:
      pp_cxx_identifier (cxx_pp, "__typeof__");
      pp_cxx_whitespace (cxx_pp);
      pp_cxx_left_paren (cxx_pp);
      dump_expr (TYPEOF_TYPE_EXPR (t), flags & ~TFF_EXPR_IN_PARENS);
      pp_cxx_right_paren (cxx_pp);
      break;

    default:
      pp_unsupported_tree (cxx_pp, t);
      /* Fall through to error.  */

    case ERROR_MARK:
      pp_identifier (cxx_pp, "<type error>");
      break;
    }
}