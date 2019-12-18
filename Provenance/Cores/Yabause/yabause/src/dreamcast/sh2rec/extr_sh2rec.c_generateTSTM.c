#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_13__ {int cycles; int pc; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ROTCL ; 
 int /*<<< orphan*/  OP_ROTCR ; 
 int /*<<< orphan*/  OP_TST ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitSHIFT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateTSTM(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);

    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitMOVLL4(b, R9, 0, R1);       /* R1 <- MappedMemoryReadByte */
    emitMOVLLG(b, 17);              /* R0 <- sh2[GBR] */
    emitMOVLL4(b, R8, 0, R4);       /* R4 <- sh2[R0] */
    emitJSR(b, R1);                 /* Call MappedMemoryReadByte */
    emitALU(b, R0, R4, OP_ADD);     /* R4 <- R4 + R0 (delay slot) */
    emitMOV(b, R0, R5);             /* R5 <- R0 (byte read) */
    emitMOVI(b, imm, R3);           /* R3 <- immediate value */
    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitSHIFT(b, R0, OP_ROTCR);     /* Rotate SH2's T Bit in place */
    emitALU(b, R3, R5, OP_TST);     /* T <- 1 if (R5 & imm) == 0, 0 otherwise */
    emitSHIFT(b, R0, OP_ROTCL);     /* Rotate T back to SH2 reg */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */

    b->cycles += 3;                 /* 3 Cycles */
    b->pc += 2;
}