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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SWAP (int /*<<< orphan*/ ) ; 
 int cc_needed (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  current_entry ; 
 int reg0 ; 

__attribute__((used)) static int opSWAP(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG0;
    JIT_EMIT_GET_OP1_REGISTER(current_entry, reg0*4);
    const int do_cc = cc_needed(state, opcode);
    JIT_EMIT_SWAP(current_entry);
    if (do_cc) JIT_EMIT_SETCC_LOGIC_L(current_entry);
    JIT_EMIT_SET_REGISTER_L(current_entry, reg0*4);
    JIT_EMIT_ADD_CYCLES(current_entry, 4);
    return 0;
}