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
struct change {scalar_t__ line0; scalar_t__ deleted; scalar_t__ line1; scalar_t__ inserted; scalar_t__ ignore; struct change* link; } ;
typedef  scalar_t__ lin ;

/* Variables and functions */
 int LIN_MAX ; 
 int /*<<< orphan*/  abort () ; 
 int context ; 

__attribute__((used)) static struct change *
find_hunk (struct change *start)
{
  struct change *prev;
  lin top0, top1;
  lin thresh;

  /* Threshold distance is 2 * CONTEXT + 1 between two non-ignorable
     changes, but only CONTEXT if one is ignorable.  Watch out for
     integer overflow, though.  */
  lin non_ignorable_threshold =
    (LIN_MAX - 1) / 2 < context ? LIN_MAX : 2 * context + 1;
  lin ignorable_threshold = context;

  do
    {
      /* Compute number of first line in each file beyond this changed.  */
      top0 = start->line0 + start->deleted;
      top1 = start->line1 + start->inserted;
      prev = start;
      start = start->link;
      thresh = (prev->ignore || (start && start->ignore)
		? ignorable_threshold
		: non_ignorable_threshold);
      /* It is not supposed to matter which file we check in the end-test.
	 If it would matter, crash.  */
      if (start && start->line0 - top0 != start->line1 - top1)
	abort ();
    } while (start
	     /* Keep going if less than THRESH lines
		elapse before the affected line.  */
	     && start->line0 - top0 < thresh);

  return prev;
}