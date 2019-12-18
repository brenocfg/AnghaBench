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
struct TYPE_3__ {scalar_t__ code; int /*<<< orphan*/  intval; } ;
struct decision_test {scalar_t__ type; struct decision_test* next; TYPE_1__ u; } ;
struct TYPE_4__ {int /*<<< orphan*/  first; } ;
struct decision {TYPE_2__ success; struct decision_test* tests; } ;
typedef  enum routine_type { ____Placeholder_routine_type } routine_type ;

/* Variables and functions */
 scalar_t__ CONST_INT ; 
 scalar_t__ DT_code ; 
 scalar_t__ DT_const_int ; 
 scalar_t__ DT_elt_zero_wide_safe ; 
 int /*<<< orphan*/  MAX_SAVED_CONST_INT ; 
 int is_unconditional (struct decision_test*,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  write_action (struct decision*,struct decision_test*,int,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_cond (struct decision_test*,int,int) ; 

__attribute__((used)) static int
write_node (struct decision *p, int depth,
	    enum routine_type subroutine_type)
{
  struct decision_test *test, *last_test;
  int uncond;

  /* Scan the tests and simplify comparisons against small
     constants.  */
  for (test = p->tests; test; test = test->next)
    {
      if (test->type == DT_code
	  && test->u.code == CONST_INT
	  && test->next
	  && test->next->type == DT_elt_zero_wide_safe
	  && -MAX_SAVED_CONST_INT <= test->next->u.intval
	  && test->next->u.intval <= MAX_SAVED_CONST_INT)
	{
	  test->type = DT_const_int;
	  test->u.intval = test->next->u.intval;
	  test->next = test->next->next;
	}
    }

  last_test = test = p->tests;
  uncond = is_unconditional (test, subroutine_type);
  if (uncond == 0)
    {
      printf ("  if (");
      write_cond (test, depth, subroutine_type);

      while ((test = test->next) != NULL)
	{
	  last_test = test;
	  if (is_unconditional (test, subroutine_type))
	    break;

	  printf ("\n      && ");
	  write_cond (test, depth, subroutine_type);
	}

      printf (")\n");
    }

  write_action (p, last_test, depth, uncond, p->success.first, subroutine_type);

  return uncond > 0;
}