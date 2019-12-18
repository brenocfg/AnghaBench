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
typedef  int /*<<< orphan*/  cxx_pretty_printer ;

/* Variables and functions */
 int const BOUND_TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ TEMPLATE_PARM_IDX (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_PARM_LEVEL (int /*<<< orphan*/ ) ; 
 int const TEMPLATE_TEMPLATE_PARM ; 
 int const TEMPLATE_TYPE_PARM ; 
 int /*<<< orphan*/  TEMPLATE_TYPE_PARM_INDEX (int /*<<< orphan*/ ) ; 
 int TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pp_cxx_begin_template_argument_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_end_template_argument_list (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_cxx_identifier (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  pp_minus (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pp_wide_integer (int /*<<< orphan*/ *,scalar_t__) ; 

void
pp_cxx_canonical_template_parameter (cxx_pretty_printer *pp, tree parm)
{
  const enum tree_code code = TREE_CODE (parm);

  /* Brings type template parameters to the canonical forms.  */
  if (code == TEMPLATE_TYPE_PARM || code == TEMPLATE_TEMPLATE_PARM
      || code == BOUND_TEMPLATE_TEMPLATE_PARM)
    parm = TEMPLATE_TYPE_PARM_INDEX (parm);

  pp_cxx_begin_template_argument_list (pp);
  pp_cxx_identifier (pp, "template-parameter-");
  pp_wide_integer (pp, TEMPLATE_PARM_LEVEL (parm));
  pp_minus (pp);
  pp_wide_integer (pp, TEMPLATE_PARM_IDX (parm) + 1);
  pp_cxx_end_template_argument_list (pp);
}