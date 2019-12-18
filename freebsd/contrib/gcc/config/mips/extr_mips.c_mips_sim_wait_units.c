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
struct mips_sim {scalar_t__ insns_left; int /*<<< orphan*/  dfa_state; } ;
typedef  int /*<<< orphan*/  state_t ;
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
 int /*<<< orphan*/  alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_sim_next_cycle (struct mips_sim*) ; 
 int /*<<< orphan*/  state_size () ; 
 scalar_t__ state_transition (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_sim_wait_units (struct mips_sim *state, rtx insn)
{
  state_t tmp_state;

  tmp_state = alloca (state_size ());
  while (state->insns_left == 0
	 || (memcpy (tmp_state, state->dfa_state, state_size ()),
	     state_transition (tmp_state, insn) >= 0))
    mips_sim_next_cycle (state);
}