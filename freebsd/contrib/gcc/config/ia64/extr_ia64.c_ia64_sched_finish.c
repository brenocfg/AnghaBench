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
struct TYPE_2__ {int /*<<< orphan*/  next_tail; int /*<<< orphan*/  prev_head; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int INSN_UID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NEXT_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PREV_INSN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bundling (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* current_sched_info ; 
 int /*<<< orphan*/  final_emit_insn_group_barriers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 scalar_t__ reload_completed ; 

__attribute__((used)) static void
ia64_sched_finish (FILE *dump, int sched_verbose)
{
  if (sched_verbose)
    fprintf (dump, "// Finishing schedule.\n");
  if (!reload_completed)
    return;
  if (reload_completed)
    {
      final_emit_insn_group_barriers (dump);
      bundling (dump, sched_verbose, current_sched_info->prev_head,
		current_sched_info->next_tail);
      if (sched_verbose && dump)
	fprintf (dump, "//    finishing %d-%d\n",
		 INSN_UID (NEXT_INSN (current_sched_info->prev_head)),
		 INSN_UID (PREV_INSN (current_sched_info->next_tail)));

      return;
    }
}