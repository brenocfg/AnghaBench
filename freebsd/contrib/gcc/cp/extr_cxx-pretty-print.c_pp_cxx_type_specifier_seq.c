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
#define  BOUND_TEMPLATE_TEMPLATE_PARM 133 
 int /*<<< orphan*/  DECL_CONSTRUCTOR_P (int /*<<< orphan*/ ) ; 
 int FUNCTION_DECL ; 
#define  METHOD_TYPE 132 
#define  TEMPLATE_DECL 131 
#define  TEMPLATE_TEMPLATE_PARM 130 
#define  TEMPLATE_TYPE_PARM 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 128 
 int /*<<< orphan*/  TYPE_METHOD_BASETYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_specifier_qualifier_list (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_nested_name_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_simple_type_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_space_for_pointer_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_type_specifier_seq (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case TEMPLATE_DECL:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case TYPE_DECL:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
      pp_cxx_cv_qualifier_seq (pp, t);
      pp_cxx_simple_type_specifier (pp, t);
      break;

    case METHOD_TYPE:
      pp_cxx_type_specifier_seq (pp, TREE_TYPE (t));
      pp_cxx_space_for_pointer_operator (pp, TREE_TYPE (t));
      pp_cxx_nested_name_specifier (pp, TYPE_METHOD_BASETYPE (t));
      break;

    default:
      if (!(TREE_CODE (t) == FUNCTION_DECL && DECL_CONSTRUCTOR_P (t)))
	pp_c_specifier_qualifier_list (pp_c_base (pp), t);
    }
}