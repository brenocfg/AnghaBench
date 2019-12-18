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
 scalar_t__ EA_INDIRECT ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  INSN_GET_COUNT ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_IMMEDIATE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_W (int /*<<< orphan*/ ) ; 
 int SIZE_B ; 
 int SIZE_L ; 
 int SIZE_W ; 
 int cc_needed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  count ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int) ; 
 int size ; 

__attribute__((used)) static int opADSQ(Q68State *state, uint32_t opcode)
{
    const int is_sub = opcode & 0x0100;
    INSN_GET_COUNT;
    INSN_GET_SIZE;
    if (EA_MODE(opcode) == EA_ADDRESS_REG && size == 1) {
        size = 2;  // ADDQ.W #imm,An is equivalent to ADDQ.L #imm,An
    }

    JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, count);

    int cycles;
    ea_get(state, opcode, size, 1, &cycles, 2);
    if (cycles < 0) {
        return 1;
    }

    const int do_cc = cc_needed(state, opcode);
    if (is_sub) {
        if (EA_MODE(opcode) == EA_ADDRESS_REG) {
            JIT_EMIT_SUB_L(current_entry);
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_SUB_B(current_entry);
                if (do_cc) JIT_EMIT_SETCC_SUB_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_SUB_W(current_entry);
                if (do_cc) JIT_EMIT_SETCC_SUB_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_SUB_L(current_entry);
                if (do_cc) JIT_EMIT_SETCC_SUB_L(current_entry);
            }
        }
    } else {
        if (EA_MODE(opcode) == EA_ADDRESS_REG) {
            JIT_EMIT_ADD_L(current_entry);
        } else {
            if (size == SIZE_B) {
                JIT_EMIT_ADD_B(current_entry);
                if (do_cc) JIT_EMIT_SETCC_ADD_B(current_entry);
            } else if (size == SIZE_W) {
                JIT_EMIT_ADD_W(current_entry);
                if (do_cc) JIT_EMIT_SETCC_ADD_W(current_entry);
            } else {  // size == SIZE_L
                JIT_EMIT_ADD_L(current_entry);
                if (do_cc) JIT_EMIT_SETCC_ADD_L(current_entry);
            }
        }
    }

    ea_set(state, opcode, size);

    cycles += (size==SIZE_L || EA_MODE(opcode) == EA_ADDRESS_REG ? 8 : 4);
    cycles += (EA_MODE(opcode) >= EA_INDIRECT ? 4 : 0);
    JIT_EMIT_ADD_CYCLES(current_entry, cycles);
    return 0;
}