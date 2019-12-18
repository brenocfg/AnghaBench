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
typedef  scalar_t__ tree ;

/* Variables and functions */
 scalar_t__ BOUND_TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ NULL_TREE ; 
 int /*<<< orphan*/  TEMPLATE_TEMPLATE_PARM_TEMPLATE_INFO (scalar_t__ const) ; 
 scalar_t__ TI_TEMPLATE (int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (scalar_t__ const) ; 
 int /*<<< orphan*/  add_substitution (scalar_t__) ; 
 scalar_t__ find_substitution (scalar_t__) ; 
 int /*<<< orphan*/  write_template_param (scalar_t__ const) ; 

__attribute__((used)) static void
write_template_template_param (const tree parm)
{
  tree template = NULL_TREE;

  /* PARM, a TEMPLATE_TEMPLATE_PARM, is an instantiation of the
     template template parameter.  The substitution candidate here is
     only the template.  */
  if (TREE_CODE (parm) == BOUND_TEMPLATE_TEMPLATE_PARM)
    {
      template
	= TI_TEMPLATE (TEMPLATE_TEMPLATE_PARM_TEMPLATE_INFO (parm));
      if (find_substitution (template))
	return;
    }

  /* <template-param> encodes only the template parameter position,
     not its template arguments, which is fine here.  */
  write_template_param (parm);
  if (template)
    add_substitution (template);
}