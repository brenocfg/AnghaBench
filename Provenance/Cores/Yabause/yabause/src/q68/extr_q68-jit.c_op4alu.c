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
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_IMMEDIATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUBX_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUBX_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUBX_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUBX_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUBX_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUBX_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_W (int /*<<< orphan*/ ) ; 
 scalar_t__ SIZE_B ; 
 scalar_t__ SIZE_L ; 
 scalar_t__ SIZE_W ; 
 int cc_needed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,scalar_t__,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 
 scalar_t__ size ; 

__attribute__((used)) static int op4alu(Q68State *state, uint32_t opcode)
{
    INSN_GET_SIZE;
    enum {NEGX = 0, CLR = 1, NEG = 2, NOT = 3, TST = 5} aluop;
    aluop = opcode>>9 & 7;

    if (EA_MODE(opcode) == EA_ADDRESS_REG) {  // Address registers not allowed
        return op_ill(state, opcode);
    }

    /* Retrieve the EA value */
    int cycles;
    ea_get(state, opcode, size, 1, &cycles, 1);
    if (cycles < 0) {
        return 1;
    }
    if (aluop != TST) {
        if (EA_MODE(opcode) == EA_DATA_REG) {
            if (size == SIZE_L) {
                cycles += 2;
            }
        } else {
            cycles += (size == SIZE_L) ? 8 : 4;
        }
    }

    /* Perform the actual computation */
    /* For simplicity, use the 2-argument operations with 0 or ~0 as the
     * second operand:
     *    -n =  0 - n
     *     0 =  0 & n
     *    ~n = ~0 ^ n
     *     n =  0 | n
     */
    JIT_EMIT_GET_OP2_IMMEDIATE(current_entry, aluop==NOT ? ~(uint32_t)0 : 0);
    const int do_cc = cc_needed(state, opcode);
    switch (aluop) {
        case NEGX:if (size == SIZE_B) {
                      JIT_EMIT_SUBX_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUBX_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_SUBX_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUBX_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_SUBX_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUBX_L(current_entry);
                  }
                  break;
        case NEG: if (size == SIZE_B) {
                      JIT_EMIT_SUB_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUB_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_SUB_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUB_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_SUB_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_SUB_L(current_entry);
                  }
                  break;
        case CLR: if (size == SIZE_B) {
                      JIT_EMIT_AND_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_AND_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_AND_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_L(current_entry);
                  }
                  break;
        case NOT: if (size == SIZE_B) {
                      JIT_EMIT_EOR_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_EOR_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_EOR_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_L(current_entry);
                  }
                  break;
        default:  // case TST
                  if (size == SIZE_B) {
                      JIT_EMIT_OR_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_OR_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_OR_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_LOGIC_L(current_entry);
                  }
                  break;
    }  // switch (aluop)

    /* Store the result in the proper place (if the instruction is not TST) */
    if (aluop != TST) {
        ea_set(state, opcode, size);
    }

    JIT_EMIT_ADD_CYCLES(current_entry, 4 + cycles);
    return 0;
}