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
 scalar_t__ CLASSTYPE_TEMPLATE_INSTANTIATION (int /*<<< orphan*/ ) ; 
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (scalar_t__) ; 
 int /*<<< orphan*/  TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  instantiate_class_template (int /*<<< orphan*/ ) ; 

__attribute__((used)) static tree
prep_operand (tree operand)
{
  if (operand)
    {
      if (CLASS_TYPE_P (TREE_TYPE (operand))
	  && CLASSTYPE_TEMPLATE_INSTANTIATION (TREE_TYPE (operand)))
	/* Make sure the template type is instantiated now.  */
	instantiate_class_template (TYPE_MAIN_VARIANT (TREE_TYPE (operand)));
    }

  return operand;
}