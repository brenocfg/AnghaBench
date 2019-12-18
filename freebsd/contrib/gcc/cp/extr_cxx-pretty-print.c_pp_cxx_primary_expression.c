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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
#define  BASELINK 143 
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
#define  CONST_DECL 142 
#define  FIELD_DECL 141 
#define  FUNCTION_DECL 140 
#define  INTEGER_CST 139 
#define  OVERLOAD 138 
#define  PARM_DECL 137 
#define  REAL_CST 136 
#define  RESULT_DECL 135 
#define  STMT_EXPR 134 
 int /*<<< orphan*/  STMT_EXPR_STMT (int /*<<< orphan*/ ) ; 
#define  STRING_CST 133 
#define  TEMPLATE_DECL 132 
#define  TEMPLATE_PARM_INDEX 131 
#define  TEMPLATE_TEMPLATE_PARM 130 
#define  TEMPLATE_TYPE_PARM 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  VAR_DECL 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_primary_expression (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_constant (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_id_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_left_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_right_paren (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_primary_expression (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case INTEGER_CST:
    case REAL_CST:
    case STRING_CST:
      pp_cxx_constant (pp, t);
      break;

    case BASELINK:
      t = BASELINK_FUNCTIONS (t);
    case VAR_DECL:
    case PARM_DECL:
    case FIELD_DECL:
    case FUNCTION_DECL:
    case OVERLOAD:
    case CONST_DECL:
    case TEMPLATE_DECL:
      pp_cxx_id_expression (pp, t);
      break;

    case RESULT_DECL:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case TEMPLATE_PARM_INDEX:
      pp_cxx_unqualified_id (pp, t);
      break;

    case STMT_EXPR:
      pp_cxx_left_paren (pp);
      pp_cxx_statement (pp, STMT_EXPR_STMT (t));
      pp_cxx_right_paren (pp);
      break;

    default:
      pp_c_primary_expression (pp_c_base (pp), t);
      break;
    }
}