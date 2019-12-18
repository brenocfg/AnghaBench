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
struct occurrence {scalar_t__ num_divisions; int /*<<< orphan*/  bb; struct occurrence* children; struct occurrence* next; } ;
typedef  int /*<<< orphan*/  basic_block ;

/* Variables and functions */
 int /*<<< orphan*/  CDI_POST_DOMINATORS ; 
 scalar_t__ dominated_by_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ flag_exceptions ; 
 int /*<<< orphan*/  single_noncomplex_succ (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
compute_merit (struct occurrence *occ)
{
  struct occurrence *occ_child;
  basic_block dom = occ->bb;

  for (occ_child = occ->children; occ_child; occ_child = occ_child->next)
    {
      basic_block bb;
      if (occ_child->children)
        compute_merit (occ_child);

      if (flag_exceptions)
	bb = single_noncomplex_succ (dom);
      else
	bb = dom;

      if (dominated_by_p (CDI_POST_DOMINATORS, bb, occ_child->bb))
        occ->num_divisions += occ_child->num_divisions;
    }
}