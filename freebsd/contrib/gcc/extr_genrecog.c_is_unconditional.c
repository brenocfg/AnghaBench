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
struct TYPE_3__ {int /*<<< orphan*/  num_clobbers_to_add; } ;
struct TYPE_4__ {TYPE_1__ insn; } ;
struct decision_test {scalar_t__ type; TYPE_2__ u; } ;
typedef  enum routine_type { ____Placeholder_routine_type } routine_type ;

/* Variables and functions */
 scalar_t__ DT_accept_insn ; 
 scalar_t__ DT_accept_op ; 
#define  PEEPHOLE2 130 
#define  RECOG 129 
#define  SPLIT 128 
 int /*<<< orphan*/  gcc_unreachable () ; 

__attribute__((used)) static int
is_unconditional (struct decision_test *t, enum routine_type subroutine_type)
{
  if (t->type == DT_accept_op)
    return 1;

  if (t->type == DT_accept_insn)
    {
      switch (subroutine_type)
	{
	case RECOG:
	  return (t->u.insn.num_clobbers_to_add == 0);
	case SPLIT:
	  return 1;
	case PEEPHOLE2:
	  return -1;
	default:
	  gcc_unreachable ();
	}
    }

  return 0;
}