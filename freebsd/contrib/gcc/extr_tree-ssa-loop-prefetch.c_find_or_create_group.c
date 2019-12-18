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
struct mem_ref_group {scalar_t__ step; struct mem_ref_group* next; int /*<<< orphan*/ * refs; int /*<<< orphan*/  base; } ;
typedef  scalar_t__ HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ operand_equal_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct mem_ref_group* xcalloc (int,int) ; 

__attribute__((used)) static struct mem_ref_group *
find_or_create_group (struct mem_ref_group **groups, tree base,
		      HOST_WIDE_INT step)
{
  struct mem_ref_group *group;

  for (; *groups; groups = &(*groups)->next)
    {
      if ((*groups)->step == step
	  && operand_equal_p ((*groups)->base, base, 0))
	return *groups;

      /* Keep the list of groups sorted by decreasing step.  */
      if ((*groups)->step < step)
	break;
    }

  group = xcalloc (1, sizeof (struct mem_ref_group));
  group->base = base;
  group->step = step;
  group->refs = NULL;
  group->next = *groups;
  *groups = group;

  return group;
}