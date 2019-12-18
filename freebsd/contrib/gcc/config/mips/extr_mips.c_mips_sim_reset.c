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
struct mips_sim {int /*<<< orphan*/  dfa_state; int /*<<< orphan*/  last_set; int /*<<< orphan*/  issue_rate; int /*<<< orphan*/  insns_left; scalar_t__ time; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  state_reset (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_sim_reset (struct mips_sim *state)
{
  state->time = 0;
  state->insns_left = state->issue_rate;
  memset (&state->last_set, 0, sizeof (state->last_set));
  state_reset (state->dfa_state);
}