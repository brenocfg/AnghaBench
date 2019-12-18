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
struct mips_sim {scalar_t__ insns_left; } ;

/* Variables and functions */
 int /*<<< orphan*/  mips_sim_next_cycle (struct mips_sim*) ; 

__attribute__((used)) static void
mips_sim_issue_nop (struct mips_sim *state)
{
  if (state->insns_left == 0)
    mips_sim_next_cycle (state);
  state->insns_left--;
}