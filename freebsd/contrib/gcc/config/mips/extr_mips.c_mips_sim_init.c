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
struct mips_sim {int /*<<< orphan*/  dfa_state; int /*<<< orphan*/  issue_rate; } ;
typedef  int /*<<< orphan*/  state_t ;

/* Variables and functions */
 int /*<<< orphan*/  mips_issue_rate () ; 
 int /*<<< orphan*/  mips_sim_reset (struct mips_sim*) ; 

__attribute__((used)) static void
mips_sim_init (struct mips_sim *state, state_t dfa_state)
{
  state->issue_rate = mips_issue_rate ();
  state->dfa_state = dfa_state;
  mips_sim_reset (state);
}