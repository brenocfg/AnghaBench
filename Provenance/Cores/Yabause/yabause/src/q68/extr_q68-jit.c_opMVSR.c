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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_SUPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVE_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_W ; 
 int /*<<< orphan*/  advance_PC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int opMVSR(Q68State *state, uint32_t opcode)
{
    int is_CCR;
    int ea_dest;
    int cycles;
    switch (opcode>>9 & 3) {
      case 0:  // MOVE SR,<ea>
        is_CCR = 0;
        ea_dest = 1;
        cycles = (EA_MODE(opcode) == EA_DATA_REG) ? 6 : 8;
        break;
      case 1:  // Undefined (MOVE CCR,<ea> on 68010)
        return op_ill(state, opcode);
      case 2:  // MOVE <ea>,CCR
        is_CCR = 1;
        ea_dest = 0;
        cycles = 12;
        break;
      default: // MOVE <ea>,SR (case 3)
        JIT_EMIT_CHECK_SUPER(current_entry);
        is_CCR = 0;
        ea_dest = 0;
        cycles = 12;
        break;
    }

    if (EA_MODE(opcode) == EA_ADDRESS_REG) {  // Address registers not allowed
        return op_ill(state, opcode);
    }

    /* Motorola docs say the address is read before being written, even
     * for the SR,<ea> format; also, the access size is a word even for
     * CCR operations. */
    int cycles_tmp;
    ea_get(state, opcode, SIZE_W, ea_dest, &cycles_tmp, 1);
    if (cycles_tmp < 0) {
        return 1;
    }
    cycles += cycles_tmp;

    /* Update the cycle counter (and PC) before writing the result, in case
     * a change to SR triggers an interrupt */
    JIT_EMIT_ADD_CYCLES(current_entry, cycles);
    advance_PC(state);

    if (ea_dest) {
        if (is_CCR) {
            JIT_EMIT_GET_OP1_CCR(current_entry);
        } else {
            JIT_EMIT_GET_OP1_SR(current_entry);
        }
        JIT_EMIT_MOVE_W(current_entry);
        ea_set(state, opcode, SIZE_W);
    } else {
        JIT_EMIT_MOVE_W(current_entry);
        /* No need to set condition codes--we're about to overwrite them */
        if (is_CCR) {
            JIT_EMIT_SET_CCR(current_entry);
        } else {
            JIT_EMIT_SET_SR(current_entry);
        }
    }

    return 0;
}