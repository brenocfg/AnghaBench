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
struct TYPE_3__ {scalar_t__ num_clobbers_to_add; int /*<<< orphan*/  code_number; int /*<<< orphan*/  lineno; } ;
struct TYPE_4__ {TYPE_1__ insn; } ;
struct decision_test {scalar_t__ type; TYPE_2__ u; struct decision_test* next; } ;
struct decision {struct decision_test* tests; } ;

/* Variables and functions */
 scalar_t__ DT_accept_insn ; 
 int /*<<< orphan*/  error_count ; 
 int /*<<< orphan*/  get_insn_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 

__attribute__((used)) static void
merge_accept_insn (struct decision *oldd, struct decision *addd)
{
  struct decision_test *old, *add;

  for (old = oldd->tests; old; old = old->next)
    if (old->type == DT_accept_insn)
      break;
  if (old == NULL)
    return;

  for (add = addd->tests; add; add = add->next)
    if (add->type == DT_accept_insn)
      break;
  if (add == NULL)
    return;

  /* If one node is for a normal insn and the second is for the base
     insn with clobbers stripped off, the second node should be ignored.  */

  if (old->u.insn.num_clobbers_to_add == 0
      && add->u.insn.num_clobbers_to_add > 0)
    {
      /* Nothing to do here.  */
    }
  else if (old->u.insn.num_clobbers_to_add > 0
	   && add->u.insn.num_clobbers_to_add == 0)
    {
      /* In this case, replace OLD with ADD.  */
      old->u.insn = add->u.insn;
    }
  else
    {
      message_with_line (add->u.insn.lineno, "`%s' matches `%s'",
			 get_insn_name (add->u.insn.code_number),
			 get_insn_name (old->u.insn.code_number));
      message_with_line (old->u.insn.lineno, "previous definition of `%s'",
			 get_insn_name (old->u.insn.code_number));
      error_count++;
    }
}