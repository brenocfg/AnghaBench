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
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHK_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SIZE_W ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 int op_ill (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int reg ; 

__attribute__((used)) static int op_CHK(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    JIT_EMIT_GET_OP1_REGISTER(current_entry, reg*4);

    int cycles;
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {
        return op_ill(state, opcode);
    }
    ea_get(state, opcode, SIZE_W, 0, &cycles, 2);
    if (cycles < 0) {
        return 1;
    }

    JIT_EMIT_ADD_CYCLES(current_entry, 10 + cycles);
    /* The JIT code takes care of adding the extra 34 cycles of exception
     * processing if necessary */
    JIT_EMIT_CHK_W(current_entry);
    return 0;
}