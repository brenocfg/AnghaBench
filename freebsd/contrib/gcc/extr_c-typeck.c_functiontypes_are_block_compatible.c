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
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_ARG_TYPES (int /*<<< orphan*/ ) ; 
 int type_lists_compatible_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  types_are_block_compatible (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
functiontypes_are_block_compatible (tree f1, tree f2)
{
  tree arg1, arg2;
  if (!types_are_block_compatible (TREE_TYPE (f1), TREE_TYPE (f2)))
    return false;
  arg1 = TYPE_ARG_TYPES (f1);
  arg2 = TYPE_ARG_TYPES (f2);
  /* APPLE LOCAL radar 6246965, 6196572 */
  return (!arg1) || (type_lists_compatible_p (arg1, arg2) == 1);
}