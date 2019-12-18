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
struct TYPE_2__ {struct decision* first; } ;
struct decision {struct decision* next; TYPE_1__ success; int /*<<< orphan*/  tests; int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int /*<<< orphan*/  gcc_assert (int) ; 
 int maybe_both_true_1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
maybe_both_true (struct decision *d1, struct decision *d2,
		 int toplevel)
{
  struct decision *p1, *p2;
  int cmp;

  /* Don't compare strings on the different positions in insn.  Doing so
     is incorrect and results in false matches from constructs like

	[(set (subreg:HI (match_operand:SI "register_operand" "r") 0)
	      (subreg:HI (match_operand:SI "register_operand" "r") 0))]
     vs
	[(set (match_operand:HI "register_operand" "r")
	      (match_operand:HI "register_operand" "r"))]

     If we are presented with such, we are recursing through the remainder
     of a node's success nodes (from the loop at the end of this function).
     Skip forward until we come to a position that matches.

     Due to the way position strings are constructed, we know that iterating
     forward from the lexically lower position (e.g. "00") will run into
     the lexically higher position (e.g. "1") and not the other way around.
     This saves a bit of effort.  */

  cmp = strcmp (d1->position, d2->position);
  if (cmp != 0)
    {
      gcc_assert (!toplevel);

      /* If the d2->position was lexically lower, swap.  */
      if (cmp > 0)
	p1 = d1, d1 = d2, d2 = p1;

      if (d1->success.first == 0)
	return 1;
      for (p1 = d1->success.first; p1; p1 = p1->next)
	if (maybe_both_true (p1, d2, 0))
	  return 1;

      return 0;
    }

  /* Test the current level.  */
  cmp = maybe_both_true_1 (d1->tests, d2->tests);
  if (cmp >= 0)
    return cmp;

  /* We can't prove that D1 and D2 cannot both be true.  If we are only
     to check the top level, return 1.  Otherwise, see if we can prove
     that all choices in both successors are mutually exclusive.  If
     either does not have any successors, we can't prove they can't both
     be true.  */

  if (toplevel || d1->success.first == 0 || d2->success.first == 0)
    return 1;

  for (p1 = d1->success.first; p1; p1 = p1->next)
    for (p2 = d2->success.first; p2; p2 = p2->next)
      if (maybe_both_true (p1, p2, 0))
	return 1;

  return 0;
}