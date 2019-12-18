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
typedef  scalar_t__ rtx ;

/* Variables and functions */
 scalar_t__ INSN_P (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 scalar_t__ ia64_first_cycle_multipass_dfa_lookahead_guard_spec (scalar_t__) ; 
 int /*<<< orphan*/  reload_completed ; 
 int /*<<< orphan*/  safe_group_barrier_needed (scalar_t__) ; 

__attribute__((used)) static int
ia64_first_cycle_multipass_dfa_lookahead_guard (rtx insn)
{
  gcc_assert (insn  && INSN_P (insn));
  return ((!reload_completed
	   || !safe_group_barrier_needed (insn))
	  && ia64_first_cycle_multipass_dfa_lookahead_guard_spec (insn));
}