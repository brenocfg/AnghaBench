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
struct decision {struct decision* prev; struct decision* next; TYPE_1__* tests; struct decision_head success; int /*<<< orphan*/  position; } ;
struct TYPE_2__ {scalar_t__ type; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ maybe_both_true (struct decision*,struct decision*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  merge_accept_insn (struct decision*,struct decision*) ; 
 scalar_t__ nodes_identical (struct decision*,struct decision*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
merge_trees (struct decision_head *oldh, struct decision_head *addh)
{
  struct decision *next, *add;

  if (addh->first == 0)
    return;
  if (oldh->first == 0)
    {
      *oldh = *addh;
      return;
    }

  /* Trying to merge bits at different positions isn't possible.  */
  gcc_assert (!strcmp (oldh->first->position, addh->first->position));

  for (add = addh->first; add ; add = next)
    {
      struct decision *old, *insert_before = NULL;

      next = add->next;

      /* The semantics of pattern matching state that the tests are
	 done in the order given in the MD file so that if an insn
	 matches two patterns, the first one will be used.  However,
	 in practice, most, if not all, patterns are unambiguous so
	 that their order is independent.  In that case, we can merge
	 identical tests and group all similar modes and codes together.

	 Scan starting from the end of OLDH until we reach a point
	 where we reach the head of the list or where we pass a
	 pattern that could also be true if NEW is true.  If we find
	 an identical pattern, we can merge them.  Also, record the
	 last node that tests the same code and mode and the last one
	 that tests just the same mode.

	 If we have no match, place NEW after the closest match we found.  */

      for (old = oldh->last; old; old = old->prev)
	{
	  if (nodes_identical (old, add))
	    {
	      merge_accept_insn (old, add);
	      merge_trees (&old->success, &add->success);
	      goto merged_nodes;
	    }

	  if (maybe_both_true (old, add, 0))
	    break;

	  /* Insert the nodes in DT test type order, which is roughly
	     how expensive/important the test is.  Given that the tests
	     are also ordered within the list, examining the first is
	     sufficient.  */
	  if ((int) add->tests->type < (int) old->tests->type)
	    insert_before = old;
	}

      if (insert_before == NULL)
	{
	  add->next = NULL;
	  add->prev = oldh->last;
	  oldh->last->next = add;
	  oldh->last = add;
	}
      else
	{
	  if ((add->prev = insert_before->prev) != NULL)
	    add->prev->next = add;
	  else
	    oldh->first = add;
	  add->next = insert_before;
	  insert_before->prev = add;
	}

    merged_nodes:;
    }
}