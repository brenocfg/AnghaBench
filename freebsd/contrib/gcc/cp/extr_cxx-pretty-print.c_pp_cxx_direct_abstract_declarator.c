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
#define  BOUND_TEMPLATE_TEMPLATE_PARM 136 
#define  FUNCTION_TYPE 135 
#define  METHOD_TYPE 134 
#define  RECORD_TYPE 133 
#define  REFERENCE_TYPE 132 
#define  TEMPLATE_TEMPLATE_PARM 131 
#define  TEMPLATE_TYPE_PARM 130 
 int const TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
#define  TYPENAME_TYPE 129 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_FN_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEMFUNC_P (int /*<<< orphan*/ ) ; 
#define  UNBOUND_CLASS_TEMPLATE 128 
 TYPE_1__* pp_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_before ; 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_direct_abstract_declarator (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_abstract_declarator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_cv_qualifier_seq (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_exception_specification (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_parameter_declaration_clause (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_direct_abstract_declarator (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case REFERENCE_TYPE:
      pp_cxx_abstract_declarator (pp, t);
      break;

    case RECORD_TYPE:
      if (TYPE_PTRMEMFUNC_P (t))
	pp_cxx_direct_abstract_declarator (pp, TYPE_PTRMEMFUNC_FN_TYPE (t));
      break;

    case METHOD_TYPE:
    case FUNCTION_TYPE:
      pp_cxx_parameter_declaration_clause (pp, t);
      pp_cxx_direct_abstract_declarator (pp, TREE_TYPE (t));
      if (TREE_CODE (t) == METHOD_TYPE)
	{
	  pp_base (pp)->padding = pp_before;
	  pp_cxx_cv_qualifier_seq
	    (pp, TREE_TYPE (TREE_VALUE (TYPE_ARG_TYPES (t))));
	}
      pp_cxx_exception_specification (pp, t);
      break;

    case TYPENAME_TYPE:
    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case BOUND_TEMPLATE_TEMPLATE_PARM:
    case UNBOUND_CLASS_TEMPLATE:
      break;

    default:
      pp_c_direct_abstract_declarator (pp_c_base (pp), t);
      break;
    }
}