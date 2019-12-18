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

/* Variables and functions */
 scalar_t__ TEMPLATE_DECL ; 
 scalar_t__ TEMPLATE_TEMPLATE_PARM ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_P (int /*<<< orphan*/ ) ; 
 int dependent_template_p (int /*<<< orphan*/ ) ; 
 int dependent_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  processing_template_decl ; 
 scalar_t__ type_dependent_expression_p (int /*<<< orphan*/ ) ; 
 scalar_t__ value_dependent_expression_p (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
dependent_template_arg_p (tree arg)
{
  if (!processing_template_decl)
    return false;

  if (TREE_CODE (arg) == TEMPLATE_DECL
      || TREE_CODE (arg) == TEMPLATE_TEMPLATE_PARM)
    return dependent_template_p (arg);
  else if (TYPE_P (arg))
    return dependent_type_p (arg);
  else
    return (type_dependent_expression_p (arg)
	    || value_dependent_expression_p (arg));
}