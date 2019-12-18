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
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_OR ; 
 int /*<<< orphan*/  OP_ROTCL ; 
 int /*<<< orphan*/  OP_ROTCR ; 
 int /*<<< orphan*/  OP_TST ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R2 ; 
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
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitSHIFT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateTAS(uint16_t inst, sh2rec_block_t *b) {
    int regn = INSTRUCTION_B(inst);

    emitMOVLL4(b, R9, 0, R0);       /* R0 <- MappedMemoryReadByte */
    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitJSR(b, R0);                 /* Call MappedMemoryReadByte */
    emitMOVLL4(b, R8, regn, R4);    /* R4 <- sh2[Rn] (delay slot) */
    emitMOV(b, R0, R5);             /* R5 <- R0 (byte read) */
    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitMOVI(b, 0x80, R2);          /* R2 <- 0x80 */
    emitMOVLL4(b, R8, regn, R4);    /* R4 <- sh2[Rn] */
    emitSHIFT(b, R0, OP_ROTCR);     /* Rotate SH2's T Bit in place */
    emitALU(b, R5, R5, OP_TST);     /* T <- 1 if byte == 0, 0 otherwise */
    emitSHIFT(b, R0, OP_ROTCL);     /* Rotate T back to SH2 reg */
    emitMOVLL4(b, R9, 3, R1);       /* R1 <- MappedMemoryWriteByte */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */
    emitJSR(b, R1);                 /* Call MappedMemoryWriteByte */
    emitALU(b, R2, R5, OP_OR);      /* R5 <- R5 | 0x80 (delay slot) */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */

    b->cycles += 4;                 /* 4 Cycles */
    b->pc += 2;
}