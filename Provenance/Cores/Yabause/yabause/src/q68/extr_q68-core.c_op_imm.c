#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_9__ {int SR; int /*<<< orphan*/  exception; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 scalar_t__ EA_DATA_REG ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  EX_PRIVILEGE_VIOLATION ; 
 scalar_t__ IFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_CLEAR_XCC () ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  INSN_SETNZ_SHIFT (int) ; 
#define  SIZE_B 129 
 int SIZE_L ; 
 int SIZE_TO_BYTES (int) ; 
#define  SIZE_W 128 
 int SR_C ; 
 int SR_S ; 
 int SR_V ; 
 int SR_X ; 
 int ea_get (TYPE_1__*,int,int,int,int*) ; 
 int /*<<< orphan*/  ea_set (TYPE_1__*,int,int,int) ; 
 int op_bit (TYPE_1__*,int) ; 
 int op_ill (TYPE_1__*,int) ; 
 int /*<<< orphan*/  set_SR (TYPE_1__*,int) ; 
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
    const int bytes = SIZE_TO_BYTES(size);
    const int shift = bytes*8 - 1;
    const uint32_t valuemask = ~(~1 << shift);

    /* Fetch the immediate value */
    uint32_t imm = (uint16_t)IFETCH(state);
    if (size == SIZE_B) {
        imm &= 0xFF;
    } else if (size == SIZE_L) {
        imm = imm<<16 | (uint16_t)IFETCH(state);
    }

    /* Fetch the EA operand (which may be SR or CCR) */
    int use_SR;
    int cycles;
    uint32_t ea_val;
    if ((aluop==OR || aluop==AND || aluop==EOR) && (opcode & 0x3F) == 0x3C) {
        /* xxxI #imm,SR (or CCR) use the otherwise-invalid form of an
         * immediate value destination */
        if (size == SIZE_W && !(state->SR & SR_S)) {
            state->exception = EX_PRIVILEGE_VIOLATION;
            return 0;
        }
        use_SR = 1;
        cycles = 8;  // Total instruction time is 20 cycles
        switch (size) {
          case SIZE_B: ea_val = state->SR & 0xFF; break;
          case SIZE_W: ea_val = state->SR;        break;
          default:     return op_ill(state, opcode);
        }
    } else {
        use_SR = 0;
        ea_val = ea_get(state, opcode, size, 1, &cycles);
        if (cycles < 0) {
            return 0;
        }
    }

    /* Perform the operation */
    uint32_t result;
    if (aluop == ADD || aluop == SUB) {
        INSN_CLEAR_XCC();
    } else {
        INSN_CLEAR_CC();
    }
    switch (aluop) {
        case OR:  result = ea_val | imm;
                  break;
        case AND: result = ea_val & imm;
                  break;
        case EOR: result = ea_val ^ imm;
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
                  /* fall through to... */
        case SUB: { result = (ea_val - imm) & valuemask;
                    if (((imm ^ ea_val) & (result ^ ea_val)) >> shift) {
                        state->SR |= SR_V;
                    }
                    if ((int)((imm >> shift) - (ea_val >> shift)
                                             + (result >> shift)) > 0) {
                        state->SR |= SR_C;
                        if (aluop != CMP) {
                            state->SR |= SR_X;
                        }
                    }
                    break;
                  }
        default:  // case ADD
                  result = (ea_val + imm) & valuemask;
                  if (((ea_val ^ result) & (imm ^ result)) >> shift) {
                      state->SR |= SR_V;
                  }
                  if ((int)((ea_val >> shift) + (imm >> shift)
                                              - (result >> shift)) > 0) {
                      state->SR |= SR_X | SR_C;
                  }
                  break;
    }
    INSN_SETNZ_SHIFT(result);

    /* Update the EA operand (if not CMPI) */
    if (aluop != CMP) {
        if (use_SR) {
            if (size == SIZE_W) {
                set_SR(state, result);
            } else {
                state->SR &= 0xFF00;
                state->SR |= result;
            }
        } else {
            ea_set(state, opcode, size, result);
        }
    }

    /* All done */
    return (size==SIZE_L ? 16 : 8)
        + (EA_MODE(opcode) == EA_DATA_REG ? 0 : 4) + cycles;
}