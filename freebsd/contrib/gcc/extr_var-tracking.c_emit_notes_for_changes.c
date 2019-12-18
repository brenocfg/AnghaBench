#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum emit_note_where { ____Placeholder_emit_note_where } emit_note_where ;
struct TYPE_3__ {int where; int /*<<< orphan*/  insn; } ;
typedef  TYPE_1__ emit_note_data ;

/* Variables and functions */
 int /*<<< orphan*/  changed_variables ; 
 int /*<<< orphan*/  emit_note_insn_var_location ; 
 int /*<<< orphan*/  htab_traverse (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static void
emit_notes_for_changes (rtx insn, enum emit_note_where where)
{
  emit_note_data data;

  data.insn = insn;
  data.where = where;
  htab_traverse (changed_variables, emit_note_insn_var_location, &data);
}