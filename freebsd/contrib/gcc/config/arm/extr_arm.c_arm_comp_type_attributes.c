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
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ATTRIBUTES (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_attribute (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
arm_comp_type_attributes (tree type1, tree type2)
{
  int l1, l2, s1, s2;

  /* Check for mismatch of non-default calling convention.  */
  if (TREE_CODE (type1) != FUNCTION_TYPE)
    return 1;

  /* Check for mismatched call attributes.  */
  l1 = lookup_attribute ("long_call", TYPE_ATTRIBUTES (type1)) != NULL;
  l2 = lookup_attribute ("long_call", TYPE_ATTRIBUTES (type2)) != NULL;
  s1 = lookup_attribute ("short_call", TYPE_ATTRIBUTES (type1)) != NULL;
  s2 = lookup_attribute ("short_call", TYPE_ATTRIBUTES (type2)) != NULL;

  /* Only bother to check if an attribute is defined.  */
  if (l1 | l2 | s1 | s2)
    {
      /* If one type has an attribute, the other must have the same attribute.  */
      if ((l1 != l2) || (s1 != s2))
	return 0;

      /* Disallow mixed attributes.  */
      if ((l1 & s2) || (l2 & s1))
	return 0;
    }

  /* Check for mismatched ISR attribute.  */
  l1 = lookup_attribute ("isr", TYPE_ATTRIBUTES (type1)) != NULL;
  if (! l1)
    l1 = lookup_attribute ("interrupt", TYPE_ATTRIBUTES (type1)) != NULL;
  l2 = lookup_attribute ("isr", TYPE_ATTRIBUTES (type2)) != NULL;
  if (! l2)
    l1 = lookup_attribute ("interrupt", TYPE_ATTRIBUTES (type2)) != NULL;
  if (l1 != l2)
    return 0;

  return 1;
}