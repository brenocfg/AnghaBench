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
struct decision_head {int /*<<< orphan*/ * first; } ;
typedef  enum routine_type { ____Placeholder_routine_type } routine_type ;

/* Variables and functions */
 int PEEPHOLE2 ; 
 int /*<<< orphan*/  break_out_subroutines (struct decision_head*,int) ; 
 int /*<<< orphan*/  factor_tests (struct decision_head*) ; 
 int /*<<< orphan*/  find_afterward (struct decision_head*,int /*<<< orphan*/ *) ; 
 scalar_t__ next_subroutine_number ; 
 int /*<<< orphan*/  simplify_tests (struct decision_head*) ; 
 int /*<<< orphan*/  write_subroutine (struct decision_head*,int) ; 
 int /*<<< orphan*/  write_subroutines (struct decision_head*,int) ; 

__attribute__((used)) static void
process_tree (struct decision_head *head, enum routine_type subroutine_type)
{
  if (head->first == NULL)
    {
      /* We can elide peephole2_insns, but not recog or split_insns.  */
      if (subroutine_type == PEEPHOLE2)
	return;
    }
  else
    {
      factor_tests (head);

      next_subroutine_number = 0;
      break_out_subroutines (head, 1);
      find_afterward (head, NULL);

      /* We run this after find_afterward, because find_afterward needs
	 the redundant DT_mode tests on predicates to determine whether
	 two tests can both be true or not.  */
      simplify_tests(head);

      write_subroutines (head, subroutine_type);
    }

  write_subroutine (head, subroutine_type);
}