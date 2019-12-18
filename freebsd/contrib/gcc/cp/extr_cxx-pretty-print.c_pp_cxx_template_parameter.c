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
 int /*<<< orphan*/  DECL_NAME (int /*<<< orphan*/ ) ; 
#define  PARM_DECL 130 
#define  TEMPLATE_DECL 129 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_VALUE (int /*<<< orphan*/ ) ; 
#define  TYPE_DECL 128 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_cxx_parameter_declaration (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_tree_identifier (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_unsupported_tree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pp_cxx_template_parameter (cxx_pretty_printer *pp, tree t)
{
  tree parameter =  TREE_VALUE (t);
  switch (TREE_CODE (parameter))
    {
    case TYPE_DECL:
      pp_cxx_identifier (pp, "class");
      if (DECL_NAME (parameter))
	pp_cxx_tree_identifier (pp, DECL_NAME (parameter));
      /* FIXME: Chech if we should print also default argument.  */
      break;

    case PARM_DECL:
      pp_cxx_parameter_declaration (pp, parameter);
      break;

    case TEMPLATE_DECL:
      break;

    default:
      pp_unsupported_tree (pp, t);
      break;
    }
}