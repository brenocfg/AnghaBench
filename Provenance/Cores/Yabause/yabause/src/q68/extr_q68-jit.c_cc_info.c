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
typedef  int uint16_t ;

/* Variables and functions */
#define  COND_CC 143 
#define  COND_CS 142 
#define  COND_EQ 141 
#define  COND_F 140 
#define  COND_GE 139 
#define  COND_GT 138 
#define  COND_HI 137 
#define  COND_LE 136 
#define  COND_LS 135 
#define  COND_LT 134 
#define  COND_MI 133 
#define  COND_NE 132 
#define  COND_PL 131 
#define  COND_T 130 
#define  COND_VC 129 
#define  COND_VS 128 

__attribute__((used)) static unsigned int cc_info(uint16_t opcode)
{
    const unsigned int INPUT_XNZVC  = 0x1F00;
    const unsigned int INPUT_XZ     = 0x1400;
    const unsigned int INPUT_X      = 0x1000;
    const unsigned int INPUT_N      = 0x0800;
    const unsigned int INPUT_V      = 0x0200;
    const unsigned int INPUT_NONE   = 0x0000;
    const unsigned int OUTPUT_XNZVC = 0x001F;
    const unsigned int OUTPUT_XZC   = 0x0015;
    const unsigned int OUTPUT_NZVC  = 0x000F;
    const unsigned int OUTPUT_N     = 0x0008;
    const unsigned int OUTPUT_Z     = 0x0004;
    const unsigned int OUTPUT_NONE  = 0x0000;
    static const unsigned int cond_inputs[] = {
        [COND_T ] = 0x0000,
        [COND_F ] = 0x0000,
        [COND_HI] = 0x0500,
        [COND_LS] = 0x0500,
        [COND_CC] = 0x0100,
        [COND_CS] = 0x0100,
        [COND_NE] = 0x0400,
        [COND_EQ] = 0x0400,
        [COND_VC] = 0x0200,
        [COND_VS] = 0x0200,
        [COND_PL] = 0x0800,
        [COND_MI] = 0x0800,
        [COND_GE] = 0x0A00,
        [COND_LT] = 0x0A00,
        [COND_GT] = 0x0E00,
        [COND_LE] = 0x0E00,
    };

    switch (opcode>>12) {

      case 0x0:
        if (opcode & 0x100) {
            if ((opcode>>3 & 7) == 1) {  // MOVEP
                return INPUT_NONE | OUTPUT_NONE;
            } else {  // BTST, etc. (dynamic)
                return INPUT_NONE | OUTPUT_Z;
            }
        } else if ((opcode>>6 & 3) == 3) {  // Illegal (size==3)
            return 0;
        } else {
            switch (opcode>>9 & 7) {
              case 0:  // ORI
                if ((opcode & 0xBF) == 0x3C) {  // ORI to CCR/SR
                    return INPUT_XNZVC | OUTPUT_XNZVC;
                } else {
                    return INPUT_NONE | OUTPUT_NZVC;
                }
              case 1:  // ANDI
                if ((opcode & 0xBF) == 0x3C) {  // ANDI to CCR/SR
                    return INPUT_XNZVC | OUTPUT_XNZVC;
                } else {
                    return INPUT_NONE | OUTPUT_NZVC;
                }
              case 2:  // SUBI
                return INPUT_NONE | OUTPUT_XNZVC;
              case 3:  // ADDI
                return INPUT_NONE | OUTPUT_XNZVC;
              case 4:  // BTST, etc. (static)
                return INPUT_NONE | OUTPUT_Z;
              case 5:  // EORI
                if ((opcode & 0xBF) == 0x3C) {  // EORI to CCR/SR
                    return INPUT_XNZVC | OUTPUT_XNZVC;
                } else {
                    return INPUT_NONE | OUTPUT_NZVC;
                }
              case 6:  // CMPI
                return INPUT_NONE | OUTPUT_NZVC;
              case 7:  // Illegal
                return 0;
            }
        }

      case 0x1:
      case 0x2:
      case 0x3:
        if ((opcode>>6 & 7) == 1) {  // MOVEA.[LW]
            return INPUT_NONE | OUTPUT_NONE;
        } else {  // MOVE.[BLW]
            return INPUT_NONE | OUTPUT_NZVC;
        }

      case 0x4:
        if (opcode & 0x0100) {
            switch (opcode>>6 & 3) {
              case 0:  // Illegal
              case 1:  // Illegal
                return 0;
              case 2:  // CHK
                /* N is unmodified if no exception occurs, so treat as input */
                return INPUT_N | OUTPUT_N;
              case 3:  // LEA
                return INPUT_NONE | OUTPUT_NONE;
            }
        } else {
            switch (opcode & 0x0EC0) {
              case 0x0000:  // NEGX.B
              case 0x0040:  // NEGX.W
              case 0x0080:  // NEGX.L
                return INPUT_XZ | OUTPUT_XNZVC;
              case 0x00C0:  // MOVE from SR
                return INPUT_XNZVC | OUTPUT_NONE;
              case 0x0200:  // CLR.B
              case 0x0240:  // CLR.W
              case 0x0280:  // CLR.L
                return INPUT_NONE | OUTPUT_NZVC;
              case 0x02C0:  // Illegal
                return 0;
              case 0x0400:  // NEG.B
              case 0x0440:  // NEG.W
              case 0x0480:  // NEG.L
                return INPUT_NONE | OUTPUT_XNZVC;
              case 0x04C0:  // MOVE to CCR
                return INPUT_NONE | OUTPUT_XNZVC;
              case 0x0600:  // NOT.B
              case 0x0640:  // NOT.W
              case 0x0680:  // NOT.L
                return INPUT_NONE | OUTPUT_NZVC;
              case 0x06C0:  // MOVE to SR
                return INPUT_NONE | OUTPUT_XNZVC;
              case 0x0800:  // NBCD
                return INPUT_XZ | OUTPUT_XZC;
              case 0x0840:  // PEA
                if ((opcode>>3 & 7) == 0) {  // SWAP.L
                    return INPUT_NONE | OUTPUT_NZVC;
                } else {
                    return INPUT_NONE | OUTPUT_NONE;
                }
              case 0x0880:  // MOVEM.W reglist,<ea>
              case 0x08C0:  // MOVEM.L reglist,<ea>
                if ((opcode>>3 & 7) == 0) {  // EXT.*
                    return INPUT_NONE | OUTPUT_NZVC;
                } else {
                    return INPUT_NONE | OUTPUT_NONE;
                }
              case 0x0A00:  // TST.B
              case 0x0A40:  // TST.W
              case 0x0A80:  // TST.L
              case 0x0AC0:  // TAS
                return INPUT_NONE | OUTPUT_NZVC;
              case 0x0C00:  // TST.B
                return 0;
              case 0x0C40:  // Miscellaneous
                switch (opcode>>3 & 7) {
                  case 0:  // TRAP #0-7
                  case 1:  // TRAP #8-15
                  case 2:  // LINK
                  case 3:  // UNLK
                  case 4:  // MOVE from USP
                  case 5:  // MOVE to USP
                    return INPUT_NONE | OUTPUT_NONE;
                  case 6:  // Miscellaneous
                    switch (opcode & 7) {
                      case 0:  // RESET
                      case 1:  // NOP
                        return INPUT_NONE | OUTPUT_NONE;
                      case 2:  // STOP
                      case 3:  // RTE
                        return INPUT_NONE | OUTPUT_XNZVC;
                      case 4:  // Illegal
                        return 0;
                      case 5:  // RTS
                        return INPUT_NONE | OUTPUT_NONE;
                      case 6:  // TRAPV
                        return INPUT_V | OUTPUT_NONE;
                      case 7:  // RTR
                        return INPUT_NONE | OUTPUT_XNZVC;
                    }
                  case 7:  // Illegal
                    return 0;
                }
              case 0x0C80:  // MOVEM.W <ea>,reglist
              case 0x0CC0:  // MOVEM.L <ea>,reglist
                return INPUT_NONE | OUTPUT_NONE;
              case 0x0E00:  // Illegal
              case 0x0E40:  // Illegal
                return 0;
              case 0x0E80:  // JSR
              case 0x0EC0:  // JMP
                return INPUT_NONE | OUTPUT_NONE;
            }
        }

      case 0x5:
        if ((opcode>>6 & 3) == 3) {  // Scc/DBcc
            return cond_inputs[opcode>>8 & 0xF] | OUTPUT_NONE;
        } else {  // ADDQ/SUBQ
            if ((opcode>>3 & 7) == 1) {  // Address register target
                return INPUT_NONE | OUTPUT_NONE;
            } else {  // Other target
                return INPUT_NONE | OUTPUT_XNZVC;
            }
        }

      case 0x6:
        /* Bcc/BSR */
        return cond_inputs[opcode>>8 & 0xF] | OUTPUT_NONE;

      case 0x7:
        if (opcode & 0x0100) {  // Illegal
            return 0;
        } else {  // MOVEQ
            return INPUT_NONE | OUTPUT_NZVC;
        }

      case 0x8:
        if ((opcode>>6 & 3) == 3) {  // MULS/MULU
            return INPUT_NONE | OUTPUT_NZVC;
        } else if ((opcode & 0x01F0) == 0x0100) {  // SBCD
            return INPUT_XZ | OUTPUT_XZC;
        } else {  // OR
            return INPUT_NONE | OUTPUT_NZVC;
        }

      case 0x9:
        if ((opcode>>6 & 3) == 3) {  // SUBA
            return INPUT_NONE | OUTPUT_NONE;
        } else if ((opcode & 0x0130) == 0x0100) {  // SUBX
            return INPUT_XZ | OUTPUT_XNZVC;
        } else {  // SUB
            return INPUT_NONE | OUTPUT_XNZVC;
        }

      case 0xA:
        /* Nothing here */
        return 0;

      case 0xB:
        /* CMP/CMPA/CMPM/EOR */
        return INPUT_NONE | OUTPUT_NZVC;

      case 0xC:
        if ((opcode>>6 & 3) == 3) {  // DIVS/DIVD
            return INPUT_NONE | OUTPUT_NZVC;
        } else if ((opcode & 0x01F0) == 0x0100) {  // ABCD
            return INPUT_XZ | OUTPUT_XZC;
        } else if ((opcode & 0x0130) == 0x0100) {  // EXG
            return INPUT_NONE | OUTPUT_NONE;
        } else {  // AND
            return INPUT_NONE | OUTPUT_NZVC;
        }

      case 0xD:
        if ((opcode>>6 & 3) == 3) {  // ADDA
            return INPUT_NONE | OUTPUT_NONE;
        } else if ((opcode & 0x0130) == 0x0100) {  // ADDX
            return INPUT_XZ | OUTPUT_XNZVC;
        } else {  // ADD
            return INPUT_NONE | OUTPUT_XNZVC;
        }

      case 0xE:
        /* Shift/rotate */
        return INPUT_X | OUTPUT_XNZVC;

      case 0xF:
        /* Nothing here */
        return 0;

    }  // switch (opcode>>12)

    return 0;  // Should be unreachable, but just for safety
}