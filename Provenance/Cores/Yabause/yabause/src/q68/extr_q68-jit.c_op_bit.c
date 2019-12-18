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
 unsigned int IFETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_BCHG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_BCLR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_BSET (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_BTST_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_BTST_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_IMMEDIATE (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int SIZE_B ; 
 int SIZE_L ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int) ; 
 int opMOVP (int /*<<< orphan*/ *,int) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 
 int reg ; 

__attribute__((used)) static int op_bit(Q68State *state, uint32_t opcode)
{
    /* Check early for MOVEP (coded as BTST/BCHG/BCLR/BSET Dn,An) */
    if (EA_MODE(opcode) == EA_ADDRESS_REG) {
        if (opcode & 0x0100) {
            return opMOVP(state, opcode);
        } else {
            return op_ill(state, opcode);
        }
    }

    enum {BTST = 0, BCHG = 1, BCLR = 2, BSET = 3} op = opcode>>6 & 3;
    int cycles;

    /* Get the bit number to operate on */
    if (opcode & 0x0100) {
        /* Bit number in register */
        INSN_GET_REG;
        JIT_EMIT_GET_OP1_REGISTER(current_entry, reg*4);
        cycles = 0;
    } else {
        unsigned int bitnum = IFETCH(state);
        JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, bitnum);
        cycles = 4;
    }

    /* EA operand is 32 bits when coming from a register, 8 when from memory */
    int size = (EA_MODE(opcode)==EA_DATA_REG ? SIZE_L : SIZE_B);
    int cycles_tmp;
    ea_get(state, opcode, size, 1, &cycles_tmp, 2);
    if (cycles_tmp < 0) {
        return 1;
    }
    cycles += cycles_tmp;
    if (size == SIZE_L && (op == BCLR || op == BTST)) {
        cycles += 2;
    }

    /* Perform the operation: first test the bit, then (for non-BTST cases)
     * twiddle it as appropriate.  All size-related checking is performed
     * in BTST, so the remaining operations are unsized. */
    if (size == SIZE_B) {
        JIT_EMIT_BTST_B(current_entry);
    } else {  // size == SIZE_L
        JIT_EMIT_BTST_L(current_entry);
    }
    switch (op) {
      default:   break;  // case BTST: nothing to do
      case BCHG: JIT_EMIT_BCHG(current_entry); break;
      case BCLR: JIT_EMIT_BCLR(current_entry); break;
      case BSET: JIT_EMIT_BSET(current_entry); break;
    }

    /* Update EA operand (but not for BTST) */
    if (op != BTST) {
        ea_set(state, opcode, size);
    }

    /* Update cycle counter; note that the times for BCHG.L, BCLR.L, and
     * BSET.L are maximums (though how they vary is undocumented) */
    JIT_EMIT_ADD_CYCLES(current_entry, (op==BTST ? 4 : 8) + cycles);

    return 0;
}