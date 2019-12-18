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
struct mips_sim {int /*<<< orphan*/  insns_left; int /*<<< orphan*/  dfa_state; } ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_sim_insn ; 
 int /*<<< orphan*/  mips_sim_record_set ; 
 int /*<<< orphan*/  note_stores (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mips_sim*) ; 
 int /*<<< orphan*/  state_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_sim_issue_insn (struct mips_sim *state, rtx insn)
{
  state_transition (state->dfa_state, insn);
  state->insns_left--;

  mips_sim_insn = insn;
  note_stores (PATTERN (insn), mips_sim_record_set, state);
}