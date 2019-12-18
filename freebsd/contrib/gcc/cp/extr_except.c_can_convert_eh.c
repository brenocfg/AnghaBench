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
 scalar_t__ CLASS_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ PUBLICLY_UNIQUELY_DERIVED_P (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ VOID_TYPE ; 
 int /*<<< orphan*/  at_least_as_qualified_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  non_reference (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
can_convert_eh (tree to, tree from)
{
  to = non_reference (to);
  from = non_reference (from);

  if (TREE_CODE (to) == POINTER_TYPE && TREE_CODE (from) == POINTER_TYPE)
    {
      to = TREE_TYPE (to);
      from = TREE_TYPE (from);

      if (! at_least_as_qualified_p (to, from))
	return 0;

      if (TREE_CODE (to) == VOID_TYPE)
	return 1;

      /* Else fall through.  */
    }

  if (CLASS_TYPE_P (to) && CLASS_TYPE_P (from)
      && PUBLICLY_UNIQUELY_DERIVED_P (to, from))
    return 1;

  return 0;
}