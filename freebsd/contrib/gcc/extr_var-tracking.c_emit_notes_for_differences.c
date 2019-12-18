#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {int /*<<< orphan*/  vars; } ;
typedef  TYPE_1__ dataflow_set ;

/* Variables and functions */
 int /*<<< orphan*/  EMIT_NOTE_BEFORE_INSN ; 
 int /*<<< orphan*/  emit_notes_for_changes (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_notes_for_differences_1 ; 
 int /*<<< orphan*/  emit_notes_for_differences_2 ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
emit_notes_for_differences (rtx insn, dataflow_set *old_set,
			    dataflow_set *new_set)
{
  htab_traverse (old_set->vars, emit_notes_for_differences_1, new_set->vars);
  htab_traverse (new_set->vars, emit_notes_for_differences_2, old_set->vars);
  emit_notes_for_changes (insn, EMIT_NOTE_BEFORE_INSN);
}