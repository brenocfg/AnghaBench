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
typedef  int /*<<< orphan*/  const uint16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  const READU16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int cc_info (int /*<<< orphan*/  const) ; 
 int /*<<< orphan*/  jit_PC ; 

__attribute__((used)) static unsigned int cc_needed(Q68State *state, uint16_t opcode)
{
    const uint16_t next_opcode = READU16(state, jit_PC);
    const unsigned int this_output = cc_info(opcode) & 0x1F;
    const unsigned int next_input = (cc_info(next_opcode) >> 8) & 0x1F;
    const unsigned int next_output = cc_info(next_opcode) & 0x1F;
    /* A condition code output from this instruction is known to be
     * unneeded if the following instruction (1) does not use that
     * condition code as input and (2) also outputs to the same condition
     * code.  We want to know whether there are any condition codes in the
     * current instruction's output set for which these conditions are
     * _not_ fulfilled. */
    return this_output & ~(~next_input & next_output);
}