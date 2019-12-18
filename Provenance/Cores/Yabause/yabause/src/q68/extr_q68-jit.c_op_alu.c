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
 scalar_t__ EA_MISC ; 
 scalar_t__ EA_MISC_IMMEDIATE ; 
 scalar_t__ EA_MODE (int) ; 
 scalar_t__ EA_REG (int) ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  JIT_EMIT_ADDA_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_AND_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_EOR_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_REGISTER (int /*<<< orphan*/ ,int) ; 
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
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_B (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_W (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SUBA_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SUB_W (int /*<<< orphan*/ ) ; 
 int SIZE_B ; 
 int SIZE_L ; 
 int SIZE_W ; 
 int cc_needed (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_get (int /*<<< orphan*/ *,int,int,int,int*,int) ; 
 int /*<<< orphan*/  ea_set (int /*<<< orphan*/ *,int,int) ; 
 int opADSX (int /*<<< orphan*/ *,int) ; 
 int opCMPM (int /*<<< orphan*/ *,int) ; 
 int op_BCD (int /*<<< orphan*/ *,int) ; 
 int op_EXG (int /*<<< orphan*/ *,int) ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 
 int reg ; 
 int size ; 

__attribute__((used)) static int op_alu(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_SIZE;

    /* Pass off special and invalid instructions early */
    if (size != 3) {
        if ((opcode & 0xB130) == 0x9100) {
            /* ADDX/SUBX are coded as ADD/SUB.* Dn,<ea:Rn> */
            return opADSX(state, opcode);
        }
        if ((opcode & 0xB1F0) == 0x8100) {
            /* ABCD/SBCD are coded as AND/OR.b Dn,<ea:Rn> */
            return op_BCD(state, opcode);
        }
        if ((opcode & 0xF130) == 0xC100) {
            /* EXG is coded as AND.[wl] Dn,<ea:Rn> */
            return op_EXG(state, opcode);
        }
        if ((opcode & 0xF130) == 0x8100) {
            /* OR.[wl] Dn,<ea:Rn> is invalid on the 68000 (later PACK/UNPK) */
            return op_ill(state, opcode);
        }
        if ((opcode & 0xF138) == 0xB108 && (opcode>>6 & 3) != 3) {
            /* CMPM is coded as EOR.* Dn,<ea:An> */
            return opCMPM(state, opcode);
        }
    }

    int ea_dest = opcode & 0x100;
    int areg_dest = 0;  // For ADDA/SUBA/CMPA
    enum {OR, AND, EOR, CMP, SUB, ADD} aluop;

    /* Find the instruction for the opcode group */
    switch (opcode>>12) {
        case 0x8: aluop = OR;  break;
        case 0x9: aluop = SUB; break;
        case 0xB: aluop = (((opcode>>6)+1) & 7) <= 4 ? CMP : EOR; break;
        case 0xC: aluop = AND; break;
        default:  aluop = ADD; break;  // case 0xD
    }

    /* Handle the special formats of ADDA/SUBA/CMPA */
    if ((aluop == ADD || aluop == SUB || aluop == CMP) && size == 3) {
        size = ea_dest ? SIZE_L : SIZE_W;
        ea_dest = 0;
        areg_dest = 1;
    }

    /* Retrieve the register and EA values; make sure to load operand 1
     * first, since operand 2 may be destroyed by memory operations */
    int cycles;
    if (ea_dest) {
        JIT_EMIT_GET_OP1_REGISTER(current_entry, reg*4);
        ea_get(state, opcode, size, ea_dest, &cycles, 2);
    } else {
        ea_get(state, opcode, size, ea_dest, &cycles, 1);
        if (areg_dest) {
            JIT_EMIT_GET_OP2_REGISTER(current_entry, (8+reg)*4);
        } else {
            JIT_EMIT_GET_OP2_REGISTER(current_entry, reg*4);
        }
    }
    if (cycles < 0) {
        return 1;
    }
    if (size == SIZE_L || areg_dest) {
        cycles += 4;
    }
    if (ea_dest) {
        cycles += 4;
    } else if ((aluop == CMP && areg_dest)
               || (size == SIZE_L
                   && (EA_MODE(opcode) <= EA_ADDRESS_REG
                       || (EA_MODE(opcode) == EA_MISC
                           && EA_REG(opcode) == EA_MISC_IMMEDIATE)))) {
        cycles -= 2;
    }

    /* Perform the actual computation */
    const int do_cc = cc_needed(state, opcode);
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
        case CMP: if (areg_dest && size == SIZE_W) {
                      JIT_EMIT_SUBA_W(current_entry);
                      if (do_cc) JIT_EMIT_SETCC_CMP_W(current_entry);
                  } else if (size == SIZE_B) {
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
        case SUB: if (areg_dest && size == SIZE_W) {
                      JIT_EMIT_SUBA_W(current_entry);
                  } else if (areg_dest && size == SIZE_L) {
                      JIT_EMIT_SUB_L(current_entry);
                  } else if (size == SIZE_B) {
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
                  if (areg_dest && size == SIZE_W) {
                      JIT_EMIT_ADDA_W(current_entry);
                  } else if (areg_dest && size == SIZE_L) {
                      JIT_EMIT_ADD_L(current_entry);
                  } else if (size == SIZE_B) {
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
    }  // switch (aluop)

    /* Store the result in the proper place (if the instruction is not CMP) */
    if (aluop != CMP) {
        if (ea_dest) {
            ea_set(state, opcode, size);
        } else if (areg_dest) {
            JIT_EMIT_SET_REGISTER_L(current_entry, (8+reg)*4);
        } else if (size == SIZE_B) {
            JIT_EMIT_SET_REGISTER_B(current_entry, reg*4);
        } else if (size == SIZE_W) {
            JIT_EMIT_SET_REGISTER_W(current_entry, reg*4);
        } else {  // size == SIZE_L
            JIT_EMIT_SET_REGISTER_L(current_entry, reg*4);
        }
    }

    JIT_EMIT_ADD_CYCLES(current_entry, 4 + cycles);
    return 0;
}