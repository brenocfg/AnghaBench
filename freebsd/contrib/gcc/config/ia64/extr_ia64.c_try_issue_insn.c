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
struct bundle_state {int /*<<< orphan*/  dfa_state; } ;
typedef  scalar_t__ rtx ;

/* Variables and functions */
 int FALSE ; 
 int TRUE ; 
 int /*<<< orphan*/  free_bundle_state (struct bundle_state*) ; 
 scalar_t__ state_transition (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static int
try_issue_insn (struct bundle_state *curr_state, rtx insn)
{
  if (insn && state_transition (curr_state->dfa_state, insn) >= 0)
    {
      free_bundle_state (curr_state);
      return FALSE;
    }
  return TRUE;
}