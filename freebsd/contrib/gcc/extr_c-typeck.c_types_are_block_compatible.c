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
 scalar_t__ BLOCK_POINTER_TYPE ; 
 scalar_t__ FUNCTION_TYPE ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_MAIN_VARIANT (int /*<<< orphan*/ ) ; 
 int functiontypes_are_block_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
types_are_block_compatible (tree lhptee, tree rhptee)
{
  if (TYPE_MAIN_VARIANT (lhptee) == TYPE_MAIN_VARIANT (rhptee))
    return true;
  if (TREE_CODE (lhptee) == FUNCTION_TYPE && TREE_CODE (rhptee) == FUNCTION_TYPE)
    return functiontypes_are_block_compatible (lhptee, rhptee);
  /* APPLE LOCAL begin radar 5882266 (C++ cm) */
  if (TREE_CODE (lhptee) == POINTER_TYPE && TREE_CODE (rhptee) == POINTER_TYPE)
    return types_are_block_compatible (TREE_TYPE (lhptee), TREE_TYPE (rhptee));
  /* APPLE LOCAL end radar 5882266 (C++ cm) */
  /* APPLE LOCAL begin radar 5988995 (C++ cm) */
  if (TREE_CODE (lhptee) == BLOCK_POINTER_TYPE
      && TREE_CODE (rhptee) == BLOCK_POINTER_TYPE)
    return types_are_block_compatible (TREE_TYPE (lhptee), TREE_TYPE (rhptee));
  /* APPLE LOCAL end radar 5988995 (C++ cm) */
  return false;
}