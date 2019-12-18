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
 int /*<<< orphan*/  COMPLETE_OR_VOID_TYPE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COMPLETE_TYPE_P (int /*<<< orphan*/ ) ; 
 scalar_t__ POINTER_TYPE ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_CLASS_TYPE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_PTRMEM_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TYPE_PTRMEM_POINTED_TO_TYPE (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
target_incomplete_p (tree type)
{
  while (true)
    if (TYPE_PTRMEM_P (type))
      {
	if (!COMPLETE_TYPE_P (TYPE_PTRMEM_CLASS_TYPE (type)))
	  return true;
	type = TYPE_PTRMEM_POINTED_TO_TYPE (type);
      }
    else if (TREE_CODE (type) == POINTER_TYPE)
      type = TREE_TYPE (type);
    else
      return !COMPLETE_OR_VOID_TYPE_P (type);
}