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
struct bundle_state {int insn_num; scalar_t__ dfa_state; } ;

/* Variables and functions */
 unsigned int CHAR_BIT ; 
 unsigned int dfa_state_size ; 

__attribute__((used)) static unsigned
bundle_state_hash (const void *bundle_state)
{
  const struct bundle_state *state = (struct bundle_state *) bundle_state;
  unsigned result, i;

  for (result = i = 0; i < dfa_state_size; i++)
    result += (((unsigned char *) state->dfa_state) [i]
	       << ((i % CHAR_BIT) * 3 + CHAR_BIT));
  return result + state->insn_num;
}