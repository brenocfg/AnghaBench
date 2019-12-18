#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct decision_test {scalar_t__ type; struct decision_test* next; } ;
struct TYPE_4__ {TYPE_1__* first; } ;
struct decision {TYPE_2__ success; struct decision_test* tests; } ;
struct TYPE_3__ {int /*<<< orphan*/  position; } ;

/* Variables and functions */
 int /*<<< orphan*/  nodes_identical_1 (struct decision_test*,struct decision_test*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
nodes_identical (struct decision *d1, struct decision *d2)
{
  struct decision_test *t1, *t2;

  for (t1 = d1->tests, t2 = d2->tests; t1 && t2; t1 = t1->next, t2 = t2->next)
    {
      if (t1->type != t2->type)
	return 0;
      if (! nodes_identical_1 (t1, t2))
	return 0;
    }

  /* For success, they should now both be null.  */
  if (t1 != t2)
    return 0;

  /* Check that their subnodes are at the same position, as any one set
     of sibling decisions must be at the same position.  Allowing this
     requires complications to find_afterward and when change_state is
     invoked.  */
  if (d1->success.first
      && d2->success.first
      && strcmp (d1->success.first->position, d2->success.first->position))
    return 0;

  return 1;
}