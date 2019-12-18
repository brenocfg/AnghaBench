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
#define  ENUMERAL_TYPE 134 
#define  RECORD_TYPE 133 
#define  TEMPLATE_PARM_INDEX 132 
#define  TEMPLATE_TEMPLATE_PARM 131 
#define  TEMPLATE_TYPE_PARM 130 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
#define  TYPENAME_TYPE 129 
 int /*<<< orphan*/  TYPE_CONTEXT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_NAME (int /*<<< orphan*/ ) ; 
#define  UNION_TYPE 128 
 int /*<<< orphan*/  pp_c_base (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_c_type_specifier (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_nested_name_specifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_qualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_unqualified_id (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_simple_type_specifier (cxx_pretty_printer *pp, tree t)
{
  switch (TREE_CODE (t))
    {
    case RECORD_TYPE:
    case UNION_TYPE:
    case ENUMERAL_TYPE:
      pp_cxx_qualified_id (pp, t);
      break;

    case TEMPLATE_TYPE_PARM:
    case TEMPLATE_TEMPLATE_PARM:
    case TEMPLATE_PARM_INDEX:
      pp_cxx_unqualified_id (pp, t);
      break;

    case TYPENAME_TYPE:
      pp_cxx_identifier (pp, "typename");
      pp_cxx_nested_name_specifier (pp, TYPE_CONTEXT (t));
      pp_cxx_unqualified_id (pp, TYPE_NAME (t));
      break;

    default:
      pp_c_type_specifier (pp_c_base (pp), t);
      break;
    }
}