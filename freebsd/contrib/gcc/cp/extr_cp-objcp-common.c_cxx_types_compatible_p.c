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
 scalar_t__ POINTER_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_REF_CAN_ALIAS_ALL (int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_ignoring_top_level_qualifiers_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ same_type_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
cxx_types_compatible_p (tree x, tree y)
{
  if (same_type_ignoring_top_level_qualifiers_p (x, y))
    return 1;

  /* Once we get to the middle-end, references and pointers are
     interchangeable.  FIXME should we try to replace all references with
     pointers?  */
  if (POINTER_TYPE_P (x) && POINTER_TYPE_P (y)
      && TYPE_MODE (x) == TYPE_MODE (y)
      && TYPE_REF_CAN_ALIAS_ALL (x) == TYPE_REF_CAN_ALIAS_ALL (y)
      && same_type_p (TREE_TYPE (x), TREE_TYPE (y)))
    return 1;

  return 0;
}