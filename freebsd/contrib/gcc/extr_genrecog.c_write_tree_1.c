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
struct decision_head {TYPE_1__* last; struct decision* first; } ;
struct decision {struct decision* next; int /*<<< orphan*/  number; scalar_t__ need_label; } ;
typedef  enum routine_type { ____Placeholder_routine_type } routine_type ;
struct TYPE_2__ {int /*<<< orphan*/  afterward; } ;

/* Variables and functions */
 int /*<<< orphan*/  OUTPUT_LABEL (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_afterward (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int write_node (struct decision*,int,int) ; 
 struct decision* write_switch (struct decision*,int) ; 

__attribute__((used)) static void
write_tree_1 (struct decision_head *head, int depth,
	      enum routine_type subroutine_type)
{
  struct decision *p, *next;
  int uncond = 0;

  for (p = head->first; p ; p = next)
    {
      /* The label for the first element was printed in write_tree.  */
      if (p != head->first && p->need_label)
	OUTPUT_LABEL (" ", p->number);

      /* Attempt to write a switch statement for a whole sequence.  */
      next = write_switch (p, depth);
      if (p != next)
	uncond = 0;
      else
	{
	  /* Failed -- fall back and write one node.  */
	  uncond = write_node (p, depth, subroutine_type);
	  next = p->next;
	}
    }

  /* Finished with this chain.  Close a fallthru path by branching
     to the afterward node.  */
  if (! uncond)
    write_afterward (head->last, head->last->afterward, "  ");
}