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
struct mips_sim {unsigned int time; TYPE_1__* last_set; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {scalar_t__ insn; unsigned int time; } ;

/* Variables and functions */
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 unsigned int HARD_REGNO_NREGS (unsigned int,int /*<<< orphan*/ ) ; 
 unsigned int REGNO (int /*<<< orphan*/ ) ; 
 scalar_t__ insn_latency (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mips_sim_next_cycle (struct mips_sim*) ; 

__attribute__((used)) static void
mips_sim_wait_reg (struct mips_sim *state, rtx insn, rtx reg)
{
  unsigned int i;

  for (i = 0; i < HARD_REGNO_NREGS (REGNO (reg), GET_MODE (reg)); i++)
    if (state->last_set[REGNO (reg) + i].insn != 0)
      {
	unsigned int t;

	t = state->last_set[REGNO (reg) + i].time;
	t += insn_latency (state->last_set[REGNO (reg) + i].insn, insn);
	while (state->time < t)
	  mips_sim_next_cycle (state);
    }
}