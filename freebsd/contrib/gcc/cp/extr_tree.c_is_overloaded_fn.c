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
 int /*<<< orphan*/  BASELINK_FUNCTIONS (int /*<<< orphan*/ ) ; 
 scalar_t__ BASELINK_P (int /*<<< orphan*/ ) ; 
 scalar_t__ COMPONENT_REF ; 
 scalar_t__ DECL_FUNCTION_TEMPLATE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ FUNCTION_DECL ; 
 scalar_t__ OFFSET_REF ; 
 scalar_t__ OVERLOAD ; 
 scalar_t__ OVL_CHAIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OVL_CURRENT (int /*<<< orphan*/ ) ; 
 scalar_t__ TEMPLATE_ID_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 

int
is_overloaded_fn (tree x)
{
  /* A baselink is also considered an overloaded function.  */
  if (TREE_CODE (x) == OFFSET_REF
      || TREE_CODE (x) == COMPONENT_REF)
    x = TREE_OPERAND (x, 1);
  if (BASELINK_P (x))
    x = BASELINK_FUNCTIONS (x);
  if (TREE_CODE (x) == TEMPLATE_ID_EXPR
      || DECL_FUNCTION_TEMPLATE_P (OVL_CURRENT (x))
      || (TREE_CODE (x) == OVERLOAD && OVL_CHAIN (x)))
    return 2;
  return  (TREE_CODE (x) == FUNCTION_DECL
	   || TREE_CODE (x) == OVERLOAD);
}