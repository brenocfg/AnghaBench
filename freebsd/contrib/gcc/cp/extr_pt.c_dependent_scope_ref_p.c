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
 scalar_t__ DECL_P (int /*<<< orphan*/ ) ; 
 scalar_t__ SCOPE_REF ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ currently_open_class (int /*<<< orphan*/ ) ; 
 scalar_t__ dependent_type_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 

__attribute__((used)) static bool
dependent_scope_ref_p (tree expression, bool criterion (tree))
{
  tree scope;
  tree name;

  gcc_assert (TREE_CODE (expression) == SCOPE_REF);

  if (!TYPE_P (TREE_OPERAND (expression, 0)))
    return true;

  scope = TREE_OPERAND (expression, 0);
  name = TREE_OPERAND (expression, 1);

  /* [temp.dep.expr]

     An id-expression is type-dependent if it contains a
     nested-name-specifier that contains a class-name that names a
     dependent type.  */
  /* The suggested resolution to Core Issue 2 implies that if the
     qualifying type is the current class, then we must peek
     inside it.  */
  if (DECL_P (name)
      && currently_open_class (scope)
      && !criterion (name))
    return false;
  if (dependent_type_p (scope))
    return true;

  return false;
}