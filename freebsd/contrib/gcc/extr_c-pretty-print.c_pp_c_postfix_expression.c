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
#define  ABS_EXPR 148 
#define  ADDR_EXPR 147 
#define  ARRAY_REF 146 
#define  CALL_EXPR 145 
#define  COMPLEX_CST 144 
#define  COMPLEX_EXPR 143 
#define  COMPONENT_REF 142 
#define  COMPOUND_LITERAL_EXPR 141 
 int /*<<< orphan*/  COMPOUND_LITERAL_EXPR_DECL (int /*<<< orphan*/ ) ; 
#define  CONSTRUCTOR 140 
 int /*<<< orphan*/  DECL_INITIAL (int /*<<< orphan*/ ) ; 
 int FUNCTION_DECL ; 
 int INDIRECT_REF ; 
#define  LTGT_EXPR 139 
#define  ORDERED_EXPR 138 
#define  POSTDECREMENT_EXPR 137 
#define  POSTINCREMENT_EXPR 136 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  UNEQ_EXPR 135 
#define  UNGE_EXPR 134 
#define  UNGT_EXPR 133 
#define  UNLE_EXPR 132 
#define  UNLT_EXPR 131 
#define  UNORDERED_EXPR 130 
#define  VA_ARG_EXPR 129 
#define  VECTOR_CST 128 
 int /*<<< orphan*/  flag_isoc99 ; 
 int /*<<< orphan*/  pp_assignment_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_arrow (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_call_argument_list (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_compound_literal (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_dot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_id_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_left_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_bracket (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_initializer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_postfix_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_primary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  pp_type_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
pp_c_postfix_expression (c_pretty_printer *pp, tree e)
{
  enum tree_code code = TREE_CODE (e);
  switch (code)
    {
    case POSTINCREMENT_EXPR:
    case POSTDECREMENT_EXPR:
      pp_postfix_expression (pp, TREE_OPERAND (e, 0));
      pp_identifier (pp, code == POSTINCREMENT_EXPR ? "++" : "--");
      break;

    case ARRAY_REF:
      pp_postfix_expression (pp, TREE_OPERAND (e, 0));
      pp_c_left_bracket (pp);
      pp_expression (pp, TREE_OPERAND (e, 1));
      pp_c_right_bracket (pp);
      break;

    case CALL_EXPR:
      pp_postfix_expression (pp, TREE_OPERAND (e, 0));
      pp_c_call_argument_list (pp, TREE_OPERAND (e, 1));
      break;

    case UNORDERED_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "isunordered"
			   : "__builtin_isunordered");
      goto two_args_fun;

    case ORDERED_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!isunordered"
			   : "!__builtin_isunordered");
      goto two_args_fun;

    case UNLT_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!isgreaterequal"
			   : "!__builtin_isgreaterequal");
      goto two_args_fun;

    case UNLE_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!isgreater"
			   : "!__builtin_isgreater");
      goto two_args_fun;

    case UNGT_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!islessequal"
			   : "!__builtin_islessequal");
      goto two_args_fun;

    case UNGE_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!isless"
			   : "!__builtin_isless");
      goto two_args_fun;

    case UNEQ_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "!islessgreater"
			   : "!__builtin_islessgreater");
      goto two_args_fun;

    case LTGT_EXPR:
      pp_c_identifier (pp, flag_isoc99
			   ? "islessgreater"
			   : "__builtin_islessgreater");
      goto two_args_fun;

    two_args_fun:
      pp_c_left_paren (pp);
      pp_expression (pp, TREE_OPERAND (e, 0));
      pp_separate_with (pp, ',');
      pp_expression (pp, TREE_OPERAND (e, 1));
      pp_c_right_paren (pp);
      break;

    case ABS_EXPR:
      pp_c_identifier (pp, "__builtin_abs");
      pp_c_left_paren (pp);
      pp_expression (pp, TREE_OPERAND (e, 0));
      pp_c_right_paren (pp);
      break;

    case COMPONENT_REF:
      {
	tree object = TREE_OPERAND (e, 0);
	if (TREE_CODE (object) == INDIRECT_REF)
	  {
	    pp_postfix_expression (pp, TREE_OPERAND (object, 0));
	    pp_c_arrow (pp);
	  }
	else
	  {
	    pp_postfix_expression (pp, object);
	    pp_c_dot (pp);
	  }
	pp_expression (pp, TREE_OPERAND (e, 1));
      }
      break;

    case COMPLEX_CST:
    case VECTOR_CST:
    case COMPLEX_EXPR:
      pp_c_compound_literal (pp, e);
      break;

    case COMPOUND_LITERAL_EXPR:
      e = DECL_INITIAL (COMPOUND_LITERAL_EXPR_DECL (e));
      /* Fall through.  */
    case CONSTRUCTOR:
      pp_initializer (pp, e);
      break;

    case VA_ARG_EXPR:
      pp_c_identifier (pp, "__builtin_va_arg");
      pp_c_left_paren (pp);
      pp_assignment_expression (pp, TREE_OPERAND (e, 0));
      pp_separate_with (pp, ',');
      pp_type_id (pp, TREE_TYPE (e));
      pp_c_right_paren (pp);
      break;

    case ADDR_EXPR:
      if (TREE_CODE (TREE_OPERAND (e, 0)) == FUNCTION_DECL)
	{
	  pp_c_id_expression (pp, TREE_OPERAND (e, 0));
	  break;
	}
      /* else fall through.  */

    default:
      pp_primary_expression (pp, e);
      break;
    }
}