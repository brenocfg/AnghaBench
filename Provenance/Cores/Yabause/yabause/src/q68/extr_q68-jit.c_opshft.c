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
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  INSN_GET_COUNT ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ASL_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ASL_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ASL_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ASR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ASR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ASR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_IMMEDIATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_LSL_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_LSL_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_LSL_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_LSR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_LSR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_LSR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROL_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROL_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROL_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXL_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXL_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXL_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ROXR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_B (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_W (int /*<<< orphan*/ ,int) ; 
 int SIZE_B ; 
 int SIZE_L ; 
 int SIZE_W ; 
 int count ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 
 int reg ; 
 int reg0 ; 
 int size ; 

__attribute__((used)) static int opshft(Q68State *state, uint32_t opcode)
{
    const int is_left = opcode & 0x0100;
    INSN_GET_SIZE;
    INSN_GET_COUNT;
    INSN_GET_REG0;
    int is_memory;
    int type;  // Shift/rotate type (0=ASL/ASR, 1=LSL/LSR, ...)
    int cycles;

    if (size == 3) {
        /* Memory shift/rotate */
        is_memory = 1;
        if ((opcode & 0x0800) || EA_MODE(opcode) <= EA_ADDRESS_REG) {
            return op_ill(state, opcode);
        }
        size = SIZE_W;
        type = opcode>>9 & 3;
        JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, 1);
        ea_get(state, opcode, size, 1, &cycles, 2);
        if (cycles < 0) {
            return 1;
        }
    } else {
        /* Register shift/rotate */
        is_memory = 0;
        type = opcode>>3 & 3;
        if (opcode & 0x0020) {
            INSN_GET_REG;
            JIT_EMIT_GET_OP1_REGISTER(current_entry, reg*4);
        } else {
            JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, count);
        }
        JIT_EMIT_GET_OP2_REGISTER(current_entry, reg0*4);
        cycles = 0;
    }

    switch (type) {
      case 0:  // ASL/ASR
        if (is_left) {
            if (size == SIZE_B) {
                JIT_EMIT_ASL_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ASL_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ASL_L(current_entry);
            }
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_ASR_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ASR_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ASR_L(current_entry);
            }
        }
        break;
      case 1:  // LSL/LSR
        if (is_left) {
            if (size == SIZE_B) {
                JIT_EMIT_LSL_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_LSL_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_LSL_L(current_entry);
            }
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_LSR_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_LSR_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_LSR_L(current_entry);
            }
        }
        break;
      case 2:  // ROXL/ROXR
        if (is_left) {
            if (size == SIZE_B) {
                JIT_EMIT_ROXL_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ROXL_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ROXL_L(current_entry);
            }
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_ROXR_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ROXR_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ROXR_L(current_entry);
            }
        }
        break;
      case 3:  // ROL/ROR
        if (is_left) {
            if (size == SIZE_B) {
                JIT_EMIT_ROL_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ROL_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ROL_L(current_entry);
            }
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_ROR_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ROR_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ROR_L(current_entry);
            }
        }
        break;
    }  // switch (type)

    if (is_memory) {
        ea_set(state, opcode, size);
    } else if (size == SIZE_B) {
        JIT_EMIT_SET_REGISTER_B(current_entry, reg0*4);
    } else if (size == SIZE_W) {
        JIT_EMIT_SET_REGISTER_W(current_entry, reg0*4);
    } else {  // size == SIZE_L
        JIT_EMIT_SET_REGISTER_L(current_entry, reg0*4);
    }

    /* Cycles based on count are added in the shift/rotate processing */
    JIT_EMIT_ADD_CYCLES(current_entry, (size==SIZE_L ? 8 : 6) + cycles);
    return 0;
}