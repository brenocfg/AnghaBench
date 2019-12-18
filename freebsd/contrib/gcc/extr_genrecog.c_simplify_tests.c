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
struct decision_test {scalar_t__ type; struct decision_test* next; } ;
struct decision_head {struct decision* first; } ;
struct decision {struct decision_head success; struct decision* next; struct decision_test* tests; } ;

/* Variables and functions */
 scalar_t__ DT_code ; 
 scalar_t__ DT_mode ; 
 scalar_t__ DT_pred ; 

__attribute__((used)) static void
simplify_tests (struct decision_head *head)
{
  struct decision *tree;

  for (tree = head->first; tree; tree = tree->next)
    {
      struct decision_test *a, *b;

      a = tree->tests;
      b = a->next;
      if (b == NULL)
	continue;

      /* Find a predicate node.  */
      while (b && b->type != DT_pred)
	b = b->next;
      if (b)
	{
	  /* Due to how these tests are constructed, we don't even need
	     to check that the mode and code are compatible -- they were
	     generated from the predicate in the first place.  */
	  while (a->type == DT_mode || a->type == DT_code)
	    a = a->next;
	  tree->tests = a;
	}
    }

  /* Recurse.  */
  for (tree = head->first; tree; tree = tree->next)
    simplify_tests (&tree->success);
}