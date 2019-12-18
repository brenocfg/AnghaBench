#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
typedef  int /*<<< orphan*/  cxx_pretty_printer ;
struct TYPE_2__ {int /*<<< orphan*/  padding; } ;

/* Variables and functions */
#define  CONST_DECL 137 
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DECL_NONSTATIC_MEMBER_FUNCTION_P (int /*<<< orphan*/ ) ; 
#define  FIELD_DECL 136 
#define  FUNCTION_DECL 135 
#define  PARM_DECL 134 
#define  TEMPLATE_DECL 133 
#define  TEMPLATE_PARM_INDEX 132 
#define  TEMPLATE_TEMPLATE_PARM 131 
#define  TEMPLATE_TYPE_PARM 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPENAME_TYPE 129 
#define  VAR_DECL 128 
 TYPE_1__* pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_before ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_direct_declarator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_exception_specification (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_id_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_implicit_parameter_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_parameter_declaration_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_space_for_pointer_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_direct_declarator (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case VAR_DECL:
    case PARM_DECL:
    case CONST_DECL:
    case FIELD_DECL:
      if (DECL_NAME (t))
	{
	  pp_cxx_space_for_pointer_operator (pp, TREE_TYPE (t));
	  pp_cxx_id_expression (pp, DECL_NAME (t));
	}
      pp_cxx_abstract_declarator (pp, TREE_TYPE (t));
      break;

    case FUNCTION_DECL:
      pp_cxx_space_for_pointer_operator (pp, TREE_TYPE (TREE_TYPE (t)));
      pp_cxx_id_expression (pp, t);
      pp_cxx_parameter_declaration_clause (pp, t);

      if (DECL_NONSTATIC_MEMBER_FUNCTION_P (t))
	{
	  pp_base (pp)->padding = pp_before;
	  pp_cxx_cv_qualifier_seq (pp, pp_cxx_implicit_parameter_type (t));
	}

      pp_cxx_exception_specification (pp, TREE_TYPE (t));
      break;

    case TYPENAME_TYPE:
    case TEMPLATE_DECL:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_PARM_INDEX:
    case TEMPLATE_TEMPLATE_PARM:
      break;

    default:
      pp_c_direct_declarator (pp_c_base (pp), t);
      break;
    }
}