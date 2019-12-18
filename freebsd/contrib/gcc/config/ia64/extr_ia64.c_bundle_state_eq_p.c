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
struct bundle_state {scalar_t__ insn_num; int /*<<< orphan*/  dfa_state; } ;

/* Variables and functions */
 int /*<<< orphan*/  dfa_state_size ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
bundle_state_eq_p (const void *bundle_state_1, const void *bundle_state_2)
{
  const struct bundle_state * state1 = (struct bundle_state *) bundle_state_1;
  const struct bundle_state * state2 = (struct bundle_state *) bundle_state_2;

  return (state1->insn_num == state2->insn_num
	  && memcmp (state1->dfa_state, state2->dfa_state,
		     dfa_state_size) == 0);
}