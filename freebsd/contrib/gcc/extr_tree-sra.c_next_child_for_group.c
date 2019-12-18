#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tree ;
struct sra_elt {struct sra_elt* sibling; int /*<<< orphan*/  element; TYPE_1__* parent; int /*<<< orphan*/  is_group; } ;
struct TYPE_2__ {struct sra_elt* children; } ;

/* Variables and functions */
 scalar_t__ RANGE_EXPR ; 
 scalar_t__ TREE_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TREE_OPERAND (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  tree_int_cst_lt (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct sra_elt *
next_child_for_group (struct sra_elt *child, struct sra_elt *group)
{
  gcc_assert (group->is_group);

  /* Find the next child in the parent.  */
  if (child)
    child = child->sibling;
  else
    child = group->parent->children;

  /* Skip siblings that do not belong to the group.  */
  while (child)
    {
      tree g_elt = group->element;
      if (TREE_CODE (g_elt) == RANGE_EXPR)
	{
	  if (!tree_int_cst_lt (child->element, TREE_OPERAND (g_elt, 0))
	      && !tree_int_cst_lt (TREE_OPERAND (g_elt, 1), child->element))
	    break;
	}
      else
	gcc_unreachable ();

      child = child->sibling;
    }

  return child;
}