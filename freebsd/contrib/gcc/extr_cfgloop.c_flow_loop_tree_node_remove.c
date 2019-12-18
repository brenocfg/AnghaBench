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
struct loop {int depth; int /*<<< orphan*/ * pred; struct loop* next; struct loop* inner; struct loop* outer; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

void
flow_loop_tree_node_remove (struct loop *loop)
{
  struct loop *prev, *father;

  father = loop->outer;
  loop->outer = NULL;

  /* Remove loop from the list of sons.  */
  if (father->inner == loop)
    father->inner = loop->next;
  else
    {
      for (prev = father->inner; prev->next != loop; prev = prev->next);
      prev->next = loop->next;
    }

  loop->depth = -1;
  free (loop->pred);
  loop->pred = NULL;
}