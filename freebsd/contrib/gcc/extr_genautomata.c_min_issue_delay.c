#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* state_t ;
typedef  int /*<<< orphan*/  ainsn_t ;
struct TYPE_4__ {int min_insn_issue_delay; } ;

/* Variables and functions */
 int /*<<< orphan*/  curr_state_pass_num ; 
 int min_issue_delay_pass_states (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
min_issue_delay (state_t state, ainsn_t ainsn)
{
  curr_state_pass_num++;
  state->min_insn_issue_delay = min_issue_delay_pass_states (state, ainsn);
  return state->min_insn_issue_delay;
}