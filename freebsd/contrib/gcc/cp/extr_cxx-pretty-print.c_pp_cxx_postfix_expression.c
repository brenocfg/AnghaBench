#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  enum tree_code { ____Placeholder_tree_code } tree_code ;
struct TYPE_20__ {int /*<<< orphan*/  enclosing_scope; } ;
typedef  TYPE_1__ cxx_pretty_printer ;

/* Variables and functions */
 int ADDR_EXPR ; 
#define  AGGR_INIT_EXPR 146 
 int /*<<< orphan*/  AGGR_INIT_VIA_CTOR_P (int /*<<< orphan*/ ) ; 
#define  ARROW_EXPR 145 
#define  BASELINK 144 
#define  CALL_EXPR 143 
#define  CONST_CAST_EXPR 142 
#define  CONST_DECL 141 
 int /*<<< orphan*/  DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/ ) ; 
#define  DYNAMIC_CAST_EXPR 140 
#define  EMPTY_CLASS_EXPR 139 
#define  FIELD_DECL 138 
#define  FUNCTION_DECL 137 
 int NOP_EXPR ; 
#define  OVERLOAD 136 
#define  PARM_DECL 135 
 int POINTER_TYPE ; 
#define  PSEUDO_DTOR_EXPR 134 
#define  REINTERPRET_CAST_EXPR 133 
#define  RESULT_DECL 132 
#define  STATIC_CAST_EXPR 131 
#define  TEMPLATE_DECL 130 
 int /*<<< orphan*/  TREE_CHAIN (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
#define  TYPEID_EXPR 129 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_c_base (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_c_postfix_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_complement (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_arrow (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_call_argument_list (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_colon_colon (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_dot (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_cxx_expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  pp_cxx_primary_expression (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_qualified_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_separate_with (TYPE_1__*,char) ; 
 int /*<<< orphan*/  pp_cxx_type_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_left_paren (TYPE_1__*) ; 
 int /*<<< orphan*/  pp_right_paren (TYPE_1__*) ; 
 int /*<<< orphan*/  strip_pointer_operator (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_postfix_expression (cxx_pretty_printer *pp, tree t)
{
  enum tree_code code = TREE_CODE (t);

  switch (code)
    {
    case AGGR_INIT_EXPR:
    case CALL_EXPR:
      {
	tree fun = TREE_OPERAND (t, 0);
	tree args = TREE_OPERAND (t, 1);
	tree saved_scope = pp->enclosing_scope;

	if (TREE_CODE (fun) == ADDR_EXPR)
	  fun = TREE_OPERAND (fun, 0);

	/* In templates, where there is no way to tell whether a given
	   call uses an actual member function.  So the parser builds
	   FUN as a COMPONENT_REF or a plain IDENTIFIER_NODE until
	   instantiation time.  */
	if (TREE_CODE (fun) != FUNCTION_DECL)
	  ;
	else if (DECL_NONSTATIC_MEMBER_FUNCTION_P (fun))
	  {
	    tree object = code == AGGR_INIT_EXPR && AGGR_INIT_VIA_CTOR_P (t)
	      ? TREE_OPERAND (t, 2)
	      : TREE_VALUE (args);

	    while (TREE_CODE (object) == NOP_EXPR)
	      object = TREE_OPERAND (object, 0);

	    if (TREE_CODE (object) == ADDR_EXPR)
	      object = TREE_OPERAND (object, 0);

	    if (TREE_CODE (TREE_TYPE (object)) != POINTER_TYPE)
	      {
		pp_cxx_postfix_expression (pp, object);
		pp_cxx_dot (pp);
	      }
	    else
	      {
		pp_cxx_postfix_expression (pp, object);
		pp_cxx_arrow (pp);
	      }
	    args = TREE_CHAIN (args);
	    pp->enclosing_scope = strip_pointer_operator (TREE_TYPE (object));
	  }

	pp_cxx_postfix_expression (pp, fun);
	pp->enclosing_scope = saved_scope;
	pp_cxx_call_argument_list (pp, args);
      }
      if (code == AGGR_INIT_EXPR && AGGR_INIT_VIA_CTOR_P (t))
	{
	  pp_cxx_separate_with (pp, ',');
	  pp_cxx_postfix_expression (pp, TREE_OPERAND (t, 2));
	}
      break;

    case BASELINK:
    case VAR_DECL:
    case PARM_DECL:
    case FIELD_DECL:
    case FUNCTION_DECL:
    case OVERLOAD:
    case CONST_DECL:
    case TEMPLATE_DECL:
    case RESULT_DECL:
      pp_cxx_primary_expression (pp, t);
      break;

    case DYNAMIC_CAST_EXPR:
    case STATIC_CAST_EXPR:
    case REINTERPRET_CAST_EXPR:
    case CONST_CAST_EXPR:
      if (code == DYNAMIC_CAST_EXPR)
	pp_cxx_identifier (pp, "dynamic_cast");
      else if (code == STATIC_CAST_EXPR)
	pp_cxx_identifier (pp, "static_cast");
      else if (code == REINTERPRET_CAST_EXPR)
	pp_cxx_identifier (pp, "reinterpret_cast");
      else
	pp_cxx_identifier (pp, "const_cast");
      pp_cxx_begin_template_argument_list (pp);
      pp_cxx_type_id (pp, TREE_TYPE (t));
      pp_cxx_end_template_argument_list (pp);
      pp_left_paren (pp);
      pp_cxx_expression (pp, TREE_OPERAND (t, 0));
      pp_right_paren (pp);
      break;

    case EMPTY_CLASS_EXPR:
      pp_cxx_type_id (pp, TREE_TYPE (t));
      pp_left_paren (pp);
      pp_right_paren (pp);
      break;

    case TYPEID_EXPR:
      t = TREE_OPERAND (t, 0);
      pp_cxx_identifier (pp, "typeid");
      pp_left_paren (pp);
      if (TYPE_P (t))
	pp_cxx_type_id (pp, t);
      else
	pp_cxx_expression (pp, t);
      pp_right_paren (pp);
      break;

    case PSEUDO_DTOR_EXPR:
      pp_cxx_postfix_expression (pp, TREE_OPERAND (t, 0));
      pp_cxx_dot (pp);
      pp_cxx_qualified_id (pp, TREE_OPERAND (t, 1));
      pp_cxx_colon_colon (pp);
      pp_complement (pp);
      pp_cxx_unqualified_id (pp, TREE_OPERAND (t, 2));
      break;

    case ARROW_EXPR:
      pp_cxx_postfix_expression (pp, TREE_OPERAND (t, 0));
      pp_cxx_arrow (pp);
      break;

    default:
      pp_c_postfix_expression (pp_c_base (pp), t);
      break;
    }
}