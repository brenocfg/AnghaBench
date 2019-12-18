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
typedef  int /*<<< orphan*/ * rtx ;
typedef  enum reg_note { ____Placeholder_reg_note } reg_note ;

/* Variables and functions */
 int /*<<< orphan*/ * XEXP (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_dependence (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  free_INSN_LIST_node (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sched_insns_conditions_mutex_p (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
add_dependence_list_and_free (rtx insn, rtx *listp, int uncond,
			      enum reg_note dep_type)
{
  rtx list, next;
  for (list = *listp, *listp = NULL; list ; list = next)
    {
      next = XEXP (list, 1);
      if (uncond || ! sched_insns_conditions_mutex_p (insn, XEXP (list, 0)))
	add_dependence (insn, XEXP (list, 0), dep_type);
      free_INSN_LIST_node (list);
    }
}