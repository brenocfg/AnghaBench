#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_145__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_145__ {int /*<<< orphan*/  pc; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_A (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INSTRUCTION_D (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MappedMemoryReadWord (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  generateADD (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateADDC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateADDI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateADDV (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateAND (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateANDI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateANDM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBF (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBFS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBRA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBRAF (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBSRF (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateBTS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCLRMAC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCLRT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPEQ (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPGE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPGT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPHI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPHS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPIM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPPL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPPZ (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateCMPSTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDIV0S (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDIV0U (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDIV1 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDMULS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDMULU (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateDT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateEXTSB (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateEXTSW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateEXTUB (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateEXTUW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateJMP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateJSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCGBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCMGBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCMSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCMVBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDCVBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSMACH (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSMACL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSMMACH (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSMMACL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSMPR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateLDSPR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMACL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMACW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOV (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBL0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBL4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBLG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBS0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBS4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVBSG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLL0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLL4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLLG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLS0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLS4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVLSG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWL0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWL4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWLG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWS0 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWS4 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMOVWSG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMULL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMULS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateMULU (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateNEG (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateNEGC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateNOP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateNOT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateOR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateORI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateORM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateROTCL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateROTCR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateROTL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateROTR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateRTE (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateRTS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSETT (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHAL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHAR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLL16 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLL2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLL8 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLR16 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLR2 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSHLR8 (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSLEEP (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCGBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCMGBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCMSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCMVBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCSR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTCVBR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSMACH (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSMACL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSMMACH (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSMMACL (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSMPR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSTSPR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSUB (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSUBC (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSUBV (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSWAPB (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateSWAPW (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateTAS (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateTRAPA (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateTST (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateTSTI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateTSTM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateXOR (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateXORI (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateXORM (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  generateXTRCT (int /*<<< orphan*/ ,TYPE_1__*) ; 

int sh2rec_rec_inst(sh2rec_block_t *b, int isdelay) {
    uint16_t inst = MappedMemoryReadWord(b->pc);
    int done = 0;

    switch(INSTRUCTION_A(inst)) {
        case 0:
            switch(INSTRUCTION_D(inst)) {
                case 2:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSTCSR(inst, b);    break;
                        case 1:  generateSTCGBR(inst, b);   break;
                        case 2:  generateSTCVBR(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 3:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateBSRF(inst, b); done = 1;   break;
                        case 2:  generateBRAF(inst, b); done = 1;   break;
                        default: return -1;
                    }
                    break;

                case 4:  generateMOVBS0(inst, b);   break;
                case 5:  generateMOVWS0(inst, b);   break;
                case 6:  generateMOVLS0(inst, b);   break;
                case 7:  generateMULL(inst, b);     break;
                case 8:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateCLRT(inst, b);     break;
                        case 1:  generateSETT(inst, b);     break;
                        case 2:  generateCLRMAC(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 9:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateNOP(inst, b);      break;
                        case 1:  generateDIV0U(inst, b);    break;
                        case 2:  generateMOVT(inst, b);     break;
                        default: return -1;
                    }
                    break;

                case 10:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSTSMACH(inst, b);  break;
                        case 1:  generateSTSMACL(inst, b);  break;
                        case 2:  generateSTSPR(inst, b);    break;
                        default: return -1;
                    }
                    break;

                case 11:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateRTS(inst, b);      done = 1;   break;
                        case 1:  generateSLEEP(inst, b);    break;
                        case 2:  generateRTE(inst, b);      done = 1;   break;
                        default: return -1;
                    }
                    break;

                case 12: generateMOVBL0(inst, b);   break;
                case 13: generateMOVWL0(inst, b);   break;
                case 14: generateMOVLL0(inst, b);   break;
                case 15: generateMACL(inst, b);     break;
                default: return -1;
            }
            break;

        case 1:  generateMOVLS4(inst, b);   break;
        case 2:
            switch(INSTRUCTION_D(inst)) {
                case 0:  generateMOVBS(inst, b);    break;
                case 1:  generateMOVWS(inst, b);    break;
                case 2:  generateMOVLS(inst, b);    break;
                case 4:  generateMOVBM(inst, b);    break;
                case 5:  generateMOVWM(inst, b);    break;
                case 6:  generateMOVLM(inst, b);    break;
                case 7:  generateDIV0S(inst, b);    break;
                case 8:  generateTST(inst, b);      break;
                case 9:  generateAND(inst, b);      break;
                case 10: generateXOR(inst, b);      break;
                case 11: generateOR(inst, b);       break;
                case 12: generateCMPSTR(inst, b);   break;
                case 13: generateXTRCT(inst, b);    break;
                case 14: generateMULU(inst, b);     break;
                case 15: generateMULS(inst, b);     break;
                default: return -1;
            }
            break;

        case 3:
            switch(INSTRUCTION_D(inst)) {
                case 0:  generateCMPEQ(inst, b);    break;
                case 2:  generateCMPHS(inst, b);    break;
                case 3:  generateCMPGE(inst, b);    break;
                case 4:  generateDIV1(inst, b);     break;
                case 5:  generateDMULU(inst, b);    break;
                case 6:  generateCMPHI(inst, b);    break;
                case 7:  generateCMPGT(inst, b);    break;
                case 8:  generateSUB(inst, b);      break;
                case 10: generateSUBC(inst, b);     break;
                case 11: generateSUBV(inst, b);     break;
                case 12: generateADD(inst, b);      break;
                case 13: generateDMULS(inst, b);    break;
                case 14: generateADDC(inst, b);     break;
                case 15: generateADDV(inst, b);     break;
                default: return -1;
            }
            break;

        case 4:
            switch(INSTRUCTION_D(inst)) {
                case 0:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSHLL(inst, b);     break;
                        case 1:  generateDT(inst, b);       break;
                        case 2:  generateSHAL(inst, b);     break;
                        default: return -1;
                    }
                    break;

                case 1:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSHLR(inst, b);     break;
                        case 1:  generateCMPPZ(inst, b);    break;
                        case 2:  generateSHAR(inst, b);     break;
                        default: return -1;
                    }
                    break;

                case 2:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSTSMMACH(inst, b); break;
                        case 1:  generateSTSMMACL(inst, b); break;
                        case 2:  generateSTSMPR(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 3:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSTCMSR(inst, b);   break;
                        case 1:  generateSTCMGBR(inst, b);  break;
                        case 2:  generateSTCMVBR(inst, b);  break;
                        default: return -1;
                    }
                    break;

                case 4:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateROTL(inst, b);     break;
                        case 2:  generateROTCL(inst, b);    break;
                        default: return -1;
                    }
                    break;

                case 5:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateROTR(inst, b);     break;
                        case 1:  generateCMPPL(inst, b);    break;
                        case 2:  generateROTCR(inst, b);    break;
                        default: return -1;
                    }
                    break;

                case 6:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateLDSMMACH(inst, b); break;
                        case 1:  generateLDSMMACL(inst, b); break;
                        case 2:  generateLDSMPR(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 7:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateLDCMSR(inst, b);   break;
                        case 1:  generateLDCMGBR(inst, b);  break;
                        case 2:  generateLDCMVBR(inst, b);  break;
                        default: return -1;
                    }
                    break;

                case 8:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSHLL2(inst, b);    break;
                        case 1:  generateSHLL8(inst, b);    break;
                        case 2:  generateSHLL16(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 9:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateSHLR2(inst, b);    break;
                        case 1:  generateSHLR8(inst, b);    break;
                        case 2:  generateSHLR16(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 10:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateLDSMACH(inst, b);  break;
                        case 1:  generateLDSMACL(inst, b);  break;
                        case 2:  generateLDSPR(inst, b);    break;
                        default: return -1;
                    }
                    break;

                case 11:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateJSR(inst, b);      done = 1;   break;
                        case 1:  generateTAS(inst, b);      break;
                        case 2:  generateJMP(inst, b);      done = 1;   break;
                        default: return -1;
                    }
                    break;

                case 14:
                    switch(INSTRUCTION_C(inst)) {
                        case 0:  generateLDCSR(inst, b);    break;
                        case 1:  generateLDCGBR(inst, b);   break;
                        case 2:  generateLDCVBR(inst, b);   break;
                        default: return -1;
                    }
                    break;

                case 15: generateMACW(inst, b);     break;
                default: return -1;
            }
            break;

        case 5:  generateMOVLL4(inst, b);   break;

        case 6:
            switch(INSTRUCTION_D(inst)) {
                case 0:  generateMOVBL(inst, b);    break;
                case 1:  generateMOVWL(inst, b);    break;
                case 2:  generateMOVLL(inst, b);    break;
                case 3:  generateMOV(inst, b);      break;
                case 4:  generateMOVBP(inst, b);    break;
                case 5:  generateMOVWP(inst, b);    break;
                case 6:  generateMOVLP(inst, b);    break;
                case 7:  generateNOT(inst, b);      break;
                case 8:  generateSWAPB(inst, b);    break;
                case 9:  generateSWAPW(inst, b);    break;
                case 10: generateNEGC(inst, b);     break;
                case 11: generateNEG(inst, b);      break;
                case 12: generateEXTUB(inst, b);    break;
                case 13: generateEXTUW(inst, b);    break;
                case 14: generateEXTSB(inst, b);    break;
                case 15: generateEXTSW(inst, b);    break;
            }
            break;

        case 7:  generateADDI(inst, b);     break;

        case 8:
            switch(INSTRUCTION_B(inst)) {
                case 0:  generateMOVBS4(inst, b);   break;
                case 1:  generateMOVWS4(inst, b);   break;
                case 4:  generateMOVBL4(inst, b);   break;
                case 5:  generateMOVWL4(inst, b);   break;
                case 8:  generateCMPIM(inst, b);    break;
                case 9:  generateBT(inst, b);       done = 1;   break;
                case 11: generateBF(inst, b);       done = 1;   break;
                case 13: generateBTS(inst, b);      done = 1;   break;
                case 15: generateBFS(inst, b);      done = 1;   break;
                default: return -1;
            }
            break;

        case 9:  generateMOVWI(inst, b);    break;
        case 10: generateBRA(inst, b);      done = 1;   break;
        case 11: generateBSR(inst, b);      done = 1;   break;

        case 12:
            switch(INSTRUCTION_B(inst)) {
                case 0:  generateMOVBSG(inst, b);   break;
                case 1:  generateMOVWSG(inst, b);   break;
                case 2:  generateMOVLSG(inst, b);   break;
                case 3:  generateTRAPA(inst, b);    done = 1;   break;
                case 4:  generateMOVBLG(inst, b);   break;
                case 5:  generateMOVWLG(inst, b);   break;
                case 6:  generateMOVLLG(inst, b);   break;
                case 7:  generateMOVA(inst, b);     break;
                case 8:  generateTSTI(inst, b);     break;
                case 9:  generateANDI(inst, b);     break;
                case 10: generateXORI(inst, b);     break;
                case 11: generateORI(inst, b);      break;
                case 12: generateTSTM(inst, b);     break;
                case 13: generateANDM(inst, b);     break;
                case 14: generateXORM(inst, b);     break;
                case 15: generateORM(inst, b);      break;
            }
            break;

        case 13: generateMOVLI(inst, b);    break;
        case 14: generateMOVI(inst, b);     break;
        default: return -1;
    }

    return done;
}