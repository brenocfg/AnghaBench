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

/* Variables and functions */
 scalar_t__ DT_accept_op ; 
 scalar_t__ maybe_both_true_2 (struct decision_test*,struct decision_test*) ; 

__attribute__((used)) static int
maybe_both_true_1 (struct decision_test *d1, struct decision_test *d2)
{
  struct decision_test *t1, *t2;

  /* A match_operand with no predicate can match anything.  Recognize
     this by the existence of a lone DT_accept_op test.  */
  if (d1->type == DT_accept_op || d2->type == DT_accept_op)
    return 1;

  /* Eliminate pairs of tests while they can exactly match.  */
  while (d1 && d2 && d1->type == d2->type)
    {
      if (maybe_both_true_2 (d1, d2) == 0)
	return 0;
      d1 = d1->next, d2 = d2->next;
    }

  /* After that, consider all pairs.  */
  for (t1 = d1; t1 ; t1 = t1->next)
    for (t2 = d2; t2 ; t2 = t2->next)
      if (maybe_both_true_2 (t1, t2) == 0)
	return 0;

  return -1;
}