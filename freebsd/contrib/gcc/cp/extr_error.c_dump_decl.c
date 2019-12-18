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
#define  ARRAY_REF 153 
#define  BASELINK 152 
 scalar_t__ BASELINK_FUNCTIONS (scalar_t__) ; 
#define  BIT_NOT_EXPR 151 
#define  CONST_DECL 150 
 int /*<<< orphan*/  CP_DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_ARTIFICIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_CLASS_SCOPE_P (scalar_t__) ; 
 scalar_t__ DECL_CONTEXT (scalar_t__) ; 
 int /*<<< orphan*/  DECL_GLOBAL_CTOR_P (scalar_t__) ; 
 int /*<<< orphan*/  DECL_GLOBAL_DTOR_P (scalar_t__) ; 
 scalar_t__ DECL_INITIAL (scalar_t__) ; 
 int /*<<< orphan*/  DECL_LANG_SPECIFIC (scalar_t__) ; 
 scalar_t__ DECL_NAME (scalar_t__) ; 
 scalar_t__ DECL_ORIGINAL_TYPE (scalar_t__) ; 
#define  ENUMERAL_TYPE 149 
#define  ERROR_MARK 148 
#define  FIELD_DECL 147 
#define  FUNCTION_DECL 146 
#define  IDENTIFIER_NODE 145 
 int /*<<< orphan*/  IDENTIFIER_TYPENAME_P (scalar_t__) ; 
#define  LABEL_DECL 144 
#define  NAMESPACE_DECL 143 
 int const NEXT_CODE (scalar_t__) ; 
#define  NON_DEPENDENT_EXPR 142 
 scalar_t__ NULL_TREE ; 
#define  OVERLOAD 141 
 int /*<<< orphan*/  OVL_CHAIN (scalar_t__) ; 
 scalar_t__ OVL_CURRENT (scalar_t__) ; 
#define  PARM_DECL 140 
#define  RECORD_TYPE 139 
#define  RESULT_DECL 138 
#define  SCOPE_REF 137 
#define  TEMPLATE_DECL 136 
#define  TEMPLATE_ID_EXPR 135 
 int TEMPLATE_PARM_INDEX ; 
#define  TEMPLATE_TYPE_PARM 134 
 int TFF_DECL_SPECIFIERS ; 
 int TFF_EXPR_IN_PARENS ; 
 int TREE_CODE (scalar_t__) ; 
 scalar_t__ TREE_OPERAND (scalar_t__,int) ; 
 scalar_t__ TREE_TYPE (scalar_t__) ; 
#define  TYPE_DECL 133 
#define  TYPE_EXPR 132 
 int /*<<< orphan*/  TYPE_P (scalar_t__) ; 
#define  UNBOUND_CLASS_TEMPLATE 131 
#define  UNION_TYPE 130 
#define  USING_DECL 129 
 scalar_t__ USING_DECL_SCOPE (scalar_t__) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  VTABLE_NAME_P (scalar_t__) ; 
 int /*<<< orphan*/  cxx_pp ; 
 int /*<<< orphan*/  dump_expr (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_function_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_global_iord (scalar_t__) ; 
 int /*<<< orphan*/  dump_scope (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  dump_simple_decl (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  dump_template_argument_list (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_template_decl (scalar_t__,int) ; 
 int /*<<< orphan*/  dump_type (scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ get_first_fn (scalar_t__) ; 
 int /*<<< orphan*/  is_overloaded_fn (scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_complement (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_declaration (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_cxx_left_bracket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_right_bracket (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pp_type_id (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
dump_decl (tree t, int flags)
{
  if (t == NULL_TREE)
    return;

  switch (TREE_CODE (t))
    {
    case TYPE_DECL:
      /* Don't say 'typedef class A' */
      if (DECL_ARTIFICIAL (t))
	{
	  if ((flags & TFF_DECL_SPECIFIERS)
	      && TREE_CODE (TREE_TYPE (t)) == TEMPLATE_TYPE_PARM)
	    /* Say `class T' not just `T'.  */
	    pp_cxx_identifier (cxx_pp, "class");

	  dump_type (TREE_TYPE (t), flags);
	  break;
	}
      if (flags & TFF_DECL_SPECIFIERS)
	pp_cxx_identifier (cxx_pp, "typedef");
      dump_simple_decl (t, DECL_ORIGINAL_TYPE (t)
			? DECL_ORIGINAL_TYPE (t) : TREE_TYPE (t),
			flags);
      break;

    case VAR_DECL:
      if (DECL_NAME (t) && VTABLE_NAME_P (DECL_NAME (t)))
	{
	  pp_string (cxx_pp, "vtable for ");
	  gcc_assert (TYPE_P (DECL_CONTEXT (t)));
	  dump_type (DECL_CONTEXT (t), flags);
	  break;
	}
      /* Else fall through.  */
    case FIELD_DECL:
    case PARM_DECL:
      dump_simple_decl (t, TREE_TYPE (t), flags);
      break;

    case RESULT_DECL:
      pp_string (cxx_pp, "<return value> ");
      dump_simple_decl (t, TREE_TYPE (t), flags);
      break;

    case NAMESPACE_DECL:
      if (flags & TFF_DECL_SPECIFIERS)
	pp_cxx_declaration (cxx_pp, t);
      else
	{
	  dump_scope (CP_DECL_CONTEXT (t), flags);
	  if (DECL_NAME (t) == NULL_TREE)
	    pp_identifier (cxx_pp, "<unnamed>");
	  else
	    pp_cxx_tree_identifier (cxx_pp, DECL_NAME (t));
	}
      break;

    case SCOPE_REF:
      pp_expression (cxx_pp, t);
      break;

    case ARRAY_REF:
      dump_decl (TREE_OPERAND (t, 0), flags);
      pp_cxx_left_bracket (cxx_pp);
      dump_decl (TREE_OPERAND (t, 1), flags);
      pp_cxx_right_bracket (cxx_pp);
      break;

      /* So that we can do dump_decl on an aggr type.  */
    case RECORD_TYPE:
    case UNION_TYPE:
    case ENUMERAL_TYPE:
      dump_type (t, flags);
      break;

    case BIT_NOT_EXPR:
      /* This is a pseudo destructor call which has not been folded into
	 a PSEUDO_DTOR_EXPR yet.  */
      pp_cxx_complement (cxx_pp);
      dump_type (TREE_OPERAND (t, 0), flags);
      break;

    case TYPE_EXPR:
      gcc_unreachable ();
      break;

      /* These special cases are duplicated here so that other functions
	 can feed identifiers to error and get them demangled properly.  */
    case IDENTIFIER_NODE:
      if (IDENTIFIER_TYPENAME_P (t))
	{
	  pp_cxx_identifier (cxx_pp, "operator");
	  /* Not exactly IDENTIFIER_TYPE_VALUE.  */
	  dump_type (TREE_TYPE (t), flags);
	  break;
	}
      else
	pp_cxx_tree_identifier (cxx_pp, t);
      break;

    case OVERLOAD:
      if (OVL_CHAIN (t))
	{
	  t = OVL_CURRENT (t);
	  if (DECL_CLASS_SCOPE_P (t))
	    {
	      dump_type (DECL_CONTEXT (t), flags);
	      pp_cxx_colon_colon (cxx_pp);
	    }
	  else if (DECL_CONTEXT (t))
	    {
	      dump_decl (DECL_CONTEXT (t), flags);
	      pp_cxx_colon_colon (cxx_pp);
	    }
	  dump_decl (DECL_NAME (t), flags);
	  break;
	}

      /* If there's only one function, just treat it like an ordinary
	 FUNCTION_DECL.  */
      t = OVL_CURRENT (t);
      /* Fall through.  */

    case FUNCTION_DECL:
      if (! DECL_LANG_SPECIFIC (t))
	pp_identifier (cxx_pp, "<built-in>");
      else if (DECL_GLOBAL_CTOR_P (t) || DECL_GLOBAL_DTOR_P (t))
	dump_global_iord (t);
      else
	dump_function_decl (t, flags);
      break;

    case TEMPLATE_DECL:
      dump_template_decl (t, flags);
      break;

    case TEMPLATE_ID_EXPR:
      {
	tree name = TREE_OPERAND (t, 0);

	if (is_overloaded_fn (name))
	  name = DECL_NAME (get_first_fn (name));
	dump_decl (name, flags);
	pp_cxx_begin_template_argument_list (cxx_pp);
	if (TREE_OPERAND (t, 1))
	  dump_template_argument_list (TREE_OPERAND (t, 1), flags);
	pp_cxx_end_template_argument_list (cxx_pp);
      }
      break;

    case LABEL_DECL:
      pp_cxx_tree_identifier (cxx_pp, DECL_NAME (t));
      break;

    case CONST_DECL:
      if ((TREE_TYPE (t) != NULL_TREE && NEXT_CODE (t) == ENUMERAL_TYPE)
	  || (DECL_INITIAL (t) &&
	      TREE_CODE (DECL_INITIAL (t)) == TEMPLATE_PARM_INDEX))
	dump_simple_decl (t, TREE_TYPE (t), flags);
      else if (DECL_NAME (t))
	dump_decl (DECL_NAME (t), flags);
      else if (DECL_INITIAL (t))
	dump_expr (DECL_INITIAL (t), flags | TFF_EXPR_IN_PARENS);
      else
	pp_identifier (cxx_pp, "<enumerator>");
      break;

    case USING_DECL:
      pp_cxx_identifier (cxx_pp, "using");
      dump_type (USING_DECL_SCOPE (t), flags);
      pp_cxx_colon_colon (cxx_pp);
      dump_decl (DECL_NAME (t), flags);
      break;

    case BASELINK:
      dump_decl (BASELINK_FUNCTIONS (t), flags);
      break;

    case NON_DEPENDENT_EXPR:
      dump_expr (t, flags);
      break;

    case TEMPLATE_TYPE_PARM:
      if (flags & TFF_DECL_SPECIFIERS)
	pp_cxx_declaration (cxx_pp, t);
      else
	pp_type_id (cxx_pp, t);
      break;

    case UNBOUND_CLASS_TEMPLATE:
      dump_type (t, flags);
      break;

    default:
      pp_unsupported_tree (cxx_pp, t);
      /* Fall through to error.  */

    case ERROR_MARK:
      pp_identifier (cxx_pp, "<declaration error>");
      break;
    }
}