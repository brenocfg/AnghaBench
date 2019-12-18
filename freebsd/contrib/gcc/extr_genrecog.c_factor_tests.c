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
struct decision_head {struct decision* first; struct decision* last; } ;
struct decision {struct decision_head success; struct decision* next; struct decision* prev; TYPE_1__* tests; int /*<<< orphan*/  position; } ;
typedef  enum decision_type { ____Placeholder_decision_type } decision_type ;
struct TYPE_2__ {int type; struct TYPE_2__* next; } ;

/* Variables and functions */
 int DT_code ; 
 int DT_elt_one_int ; 
 int DT_elt_zero_int ; 
 int DT_elt_zero_wide_safe ; 
 int DT_mode ; 
 int DT_veclen ; 
 int /*<<< orphan*/  merge_trees (struct decision_head*,struct decision_head*) ; 
 struct decision* new_decision (int /*<<< orphan*/ ,struct decision_head*) ; 

__attribute__((used)) static void
factor_tests (struct decision_head *head)
{
  struct decision *first, *next;

  for (first = head->first; first && first->next; first = next)
    {
      enum decision_type type;
      struct decision *new, *old_last;

      type = first->tests->type;
      next = first->next;

      /* Want at least two compatible sequential nodes.  */
      if (next->tests->type != type)
	continue;

      /* Don't want all node types, just those we can turn into
	 switch statements.  */
      if (type != DT_mode
	  && type != DT_code
	  && type != DT_veclen
	  && type != DT_elt_zero_int
	  && type != DT_elt_one_int
	  && type != DT_elt_zero_wide_safe)
	continue;

      /* If we'd been performing more than one test, create a new node
         below our first test.  */
      if (first->tests->next != NULL)
	{
	  new = new_decision (first->position, &first->success);
	  new->tests = first->tests->next;
	  first->tests->next = NULL;
	}

      /* Crop the node tree off after our first test.  */
      first->next = NULL;
      old_last = head->last;
      head->last = first;

      /* For each compatible test, adjust to perform only one test in
	 the top level node, then merge the node back into the tree.  */
      do
	{
	  struct decision_head h;

	  if (next->tests->next != NULL)
	    {
	      new = new_decision (next->position, &next->success);
	      new->tests = next->tests->next;
	      next->tests->next = NULL;
	    }
	  new = next;
	  next = next->next;
	  new->next = NULL;
	  h.first = h.last = new;

	  merge_trees (head, &h);
	}
      while (next && next->tests->type == type);

      /* After we run out of compatible tests, graft the remaining nodes
	 back onto the tree.  */
      if (next)
	{
	  next->prev = head->last;
	  head->last->next = next;
	  head->last = old_last;
	}
    }

  /* Recurse.  */
  for (first = head->first; first; first = first->next)
    factor_tests (&first->success);
}