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
 scalar_t__ EA_DATA_REG ; 
 int EA_MISC ; 
 int EA_MISC_IMMEDIATE ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_SUPER (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_OR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_ADD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_CMP_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_LOGIC_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SETCC_SUB_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_CCR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_SR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_W (int /*<<< orphan*/ ) ; 
#define  SIZE_B 129 
 int SIZE_L ; 
#define  SIZE_W 128 
 int /*<<< orphan*/  advance_PC (int /*<<< orphan*/ *) ; 
 int cc_needed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int) ; 
 int op_bit (int /*<<< orphan*/ *,int) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 
 int size ; 

__attribute__((used)) static int op_imm(Q68State *state, uint32_t opcode)
{
    /* Check for bit-twiddling and illegal opcodes first */
    enum {OR = 0, AND, SUB, ADD, _BIT, EOR, CMP, _ILL} aluop;
    aluop = opcode>>9 & 7;
    if (aluop == _BIT) {
        return op_bit(state, opcode);
    } else if (aluop == _ILL) {
        return op_ill(state, opcode);
    }

    /* Get the instruction size */
    INSN_GET_SIZE;
    if (size == 3) {
        return op_ill(state, opcode);
    }

    /* Fetch the immediate value */
    int cycles_dummy;
    ea_get(state, EA_MISC<<3 | EA_MISC_IMMEDIATE, size, 0, &cycles_dummy, 1);

    /* Fetch the EA operand (which may be SR or CCR) */
    int use_SR;
    int cycles;
    if ((aluop==OR || aluop==AND || aluop==EOR) && (opcode & 0x3F) == 0x3C) {
        /* xxxI #imm,SR (or CCR) use the otherwise-invalid form of an
         * immediate value destination */
        use_SR = 1;
        cycles = 8;  // Total instruction time is 20 cycles
        switch (size) {
          case SIZE_B:
            JIT_EMIT_GET_OP2_CCR(current_entry);
            break;
          case SIZE_W:
            JIT_EMIT_CHECK_SUPER(current_entry);
            JIT_EMIT_GET_OP2_SR(current_entry);
            break;
          default:
            return op_ill(state, opcode);
        }
    } else {
        use_SR = 0;
        ea_get(state, opcode, size, 1, &cycles, 2);
        if (cycles < 0) {
            return 1;
        }
    }

    /* Check whether we need to output condition codes */
    const int do_cc = cc_needed(state, opcode);

    /* Perform the operation */
    switch (aluop) {
        case OR:  if (size == SIZE_B) {
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
        case AND: if (size == SIZE_B) {
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
        case EOR: if (size == SIZE_B) {
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
        case CMP: if (size == SIZE_L) {  // CMPI takes less time in most cases
                      if (EA_MODE(opcode) != EA_DATA_REG) {
                          cycles -= 8;
                      } else {
                          cycles -= 2;
                      }
                  } else {
                      if (EA_MODE(opcode) != EA_DATA_REG) {
                          cycles -= 4;
                      }
                  }
                  if (size == SIZE_B) {
                      JIT_EMIT_SUB_B(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_CMP_B(current_entry);
                  } else if (size == SIZE_W) {
                      JIT_EMIT_SUB_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_CMP_W(current_entry);
                  } else {  // size == SIZE_L
                      JIT_EMIT_SUB_L(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_CMP_L(current_entry);
                  }
                  break;
        case SUB: if (size == SIZE_B) {
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
        default:  // case ADD
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
                  break;
    }

    /* Update the cycle counter (and PC) before writing the result, in case
     * a change to SR triggers an interrupt */
    cycles += (size==SIZE_L ? 16 : 8);
    cycles += (EA_MODE(opcode) == EA_DATA_REG ? 0 : 4);
    JIT_EMIT_ADD_CYCLES(current_entry, cycles);
    advance_PC(state);

    /* Update the EA operand (if not CMPI) */
    if (aluop != CMP) {
        if (use_SR) {
            if (size == SIZE_B) {
                JIT_EMIT_SET_CCR(current_entry);
            } else {
                JIT_EMIT_SET_SR(current_entry);
            }
        } else {
            ea_set(state, opcode, size);
        }
    }

    /* All done */
    return 0;
}