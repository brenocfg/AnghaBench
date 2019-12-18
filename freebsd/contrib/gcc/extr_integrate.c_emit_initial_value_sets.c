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
struct initial_value_struct {int num_entries; TYPE_1__* entries; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_4__ {struct initial_value_struct* hard_reg_initial_vals; } ;
struct TYPE_3__ {int /*<<< orphan*/  hard_reg; int /*<<< orphan*/  pseudo; } ;

/* Variables and functions */
 TYPE_2__* cfun ; 
 int /*<<< orphan*/  emit_insn_at_entry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit_move_insn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_sequence () ; 
 int /*<<< orphan*/  get_insns () ; 
 int /*<<< orphan*/  start_sequence () ; 

unsigned int
emit_initial_value_sets (void)
{
  struct initial_value_struct *ivs = cfun->hard_reg_initial_vals;
  int i;
  rtx seq;

  if (ivs == 0)
    return 0;

  start_sequence ();
  for (i = 0; i < ivs->num_entries; i++)
    emit_move_insn (ivs->entries[i].pseudo, ivs->entries[i].hard_reg);
  seq = get_insns ();
  end_sequence ();

  emit_insn_at_entry (seq);
  return 0;
}