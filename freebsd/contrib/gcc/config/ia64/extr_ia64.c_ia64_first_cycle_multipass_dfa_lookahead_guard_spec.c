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
 int BEGIN_DATA ; 
 scalar_t__ INSN_P (scalar_t__) ; 
 int TODO_SPEC (scalar_t__) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int pending_data_specs ; 

__attribute__((used)) static bool
ia64_first_cycle_multipass_dfa_lookahead_guard_spec (rtx insn)
{
  gcc_assert (insn  && INSN_P (insn));
  /* Size of ALAT is 32.  As far as we perform conservative data speculation,
     we keep ALAT half-empty.  */
  return (pending_data_specs < 16
	  || !(TODO_SPEC (insn) & BEGIN_DATA));
}