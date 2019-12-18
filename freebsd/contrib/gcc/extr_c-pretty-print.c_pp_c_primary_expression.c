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
#define  CONST_DECL 140 
#define  ERROR_MARK 139 
#define  FIELD_DECL 138 
#define  FUNCTION_DECL 137 
#define  IDENTIFIER_NODE 136 
#define  INTEGER_CST 135 
#define  LABEL_DECL 134 
#define  PARM_DECL 133 
#define  REAL_CST 132 
#define  RESULT_DECL 131 
#define  STRING_CST 130 
#define  TARGET_EXPR 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_ampersand (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_c_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_tree_decl_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_tree_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_initializer (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_primary_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_separate_with (int /*<<< orphan*/ *,char) ; 

void
pp_c_primary_expression (c_pretty_printer *pp, tree e)
{
  switch (TREE_CODE (e))
    {
    case VAR_DECL:
    case PARM_DECL:
    case FIELD_DECL:
    case CONST_DECL:
    case FUNCTION_DECL:
    case LABEL_DECL:
      pp_c_tree_decl_identifier (pp, e);
      break;

    case IDENTIFIER_NODE:
      pp_c_tree_identifier (pp, e);
      break;

    case ERROR_MARK:
      pp_c_identifier (pp, "<erroneous-expression>");
      break;

    case RESULT_DECL:
      pp_c_identifier (pp, "<return-value>");
      break;

    case INTEGER_CST:
    case REAL_CST:
    case STRING_CST:
      pp_c_constant (pp, e);
      break;

    case TARGET_EXPR:
      pp_c_identifier (pp, "__builtin_memcpy");
      pp_c_left_paren (pp);
      pp_ampersand (pp);
      pp_primary_expression (pp, TREE_OPERAND (e, 0));
      pp_separate_with (pp, ',');
      pp_ampersand (pp);
      pp_initializer (pp, TREE_OPERAND (e, 1));
      if (TREE_OPERAND (e, 2))
	{
	  pp_separate_with (pp, ',');
	  pp_c_expression (pp, TREE_OPERAND (e, 2));
	}
      pp_c_right_paren (pp);
      break;

    default:
      /* FIXME:  Make sure we won't get into an infinie loop.  */
      pp_c_left_paren (pp);
      pp_expression (pp, e);
      pp_c_right_paren (pp);
      break;
    }
}