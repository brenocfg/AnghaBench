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
struct decision_head {struct decision* first; } ;
struct decision {scalar_t__ subroutine_number; int need_label; struct decision* afterward; struct decision_head success; struct decision* next; } ;

/* Variables and functions */
 scalar_t__ maybe_both_true (struct decision*,struct decision*,int) ; 

__attribute__((used)) static void
find_afterward (struct decision_head *head, struct decision *real_afterward)
{
  struct decision *p, *q, *afterward;

  /* We can't propagate alternatives across subroutine boundaries.
     This is not incorrect, merely a minor optimization loss.  */

  p = head->first;
  afterward = (p->subroutine_number > 0 ? NULL : real_afterward);

  for ( ; p ; p = p->next)
    {
      /* Find the next node that might be true if this one fails.  */
      for (q = p->next; q ; q = q->next)
	if (maybe_both_true (p, q, 1))
	  break;

      /* If we reached the end of the list without finding one,
	 use the incoming afterward position.  */
      if (!q)
	q = afterward;
      p->afterward = q;
      if (q)
	q->need_label = 1;
    }

  /* Recurse.  */
  for (p = head->first; p ; p = p->next)
    if (p->success.first)
      find_afterward (&p->success, p->afterward);

  /* When we are generating a subroutine, record the real afterward
     position in the first node where write_tree can find it, and we
     can do the right thing at the subroutine call site.  */
  p = head->first;
  if (p->subroutine_number > 0)
    p->afterward = real_afterward;
}