#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_18__ {int cycles; int pc; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int INSTRUCTION_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_AND ; 
 int /*<<< orphan*/  OP_OR ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  R_SR ; 
 int /*<<< orphan*/  emitADDI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitANDI (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDC (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMACW (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVWM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTC (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateMACW(uint16_t inst, sh2rec_block_t *b) {
    int regn = INSTRUCTION_B(inst);
    int regm = INSTRUCTION_C(inst);

    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitMOVLL4(b, R8, regm, R4);    /* R4 <- sh2[Rm] */
    emitMOVLL4(b, R9, 1, R0);       /* R0 <- MappedMemoryReadWord */
    emitADDI(b, 2, R4);             /* R4 <- R4 + 2 */
    emitMOVLS4(b, R4, regm, R8);    /* sh2[Rm] <- R4 */
    emitJSR(b, R0);                 /* Call MappedMemoryReadWord */
    emitADDI(b, -2, R4);            /* R4 <- R4 - 2 (delay slot) */
    emitMOVWM(b, R0, R15);          /* Push R0 onto the stack */
    emitMOVLL4(b, R8, regn, R4);    /* R4 <- sh2[Rn] */
    emitMOVLL4(b, R9, 1, R0);       /* R0 <- MappedMemoryReadWord */
    emitADDI(b, 2, R4);             /* R4 <- R4 + 2 */
    emitMOVLS4(b, R4, regn, R8);    /* sh2[Rn] <- R4 */
    emitJSR(b, R0);                 /* Call MappedMemoryReadWord */
    emitADDI(b, -2, R4);            /* R4 <- R4 - 2 (delay slot) */
    emitMOVWM(b, R0, R15);          /* Push R0 onto the stack */
    emitSTC(b, R_SR, R2);           /* R2 <- SR */
    emitMOVI(b, 0xFD, R3);          /* R3 <- 0xFFFFFFFD */
    emitMOVLM(b, R0, R15);          /* Push R0 onto the stack */
    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitALU(b, R2, R3, OP_AND);     /* R3 <- R2 & R3 (Mask out S Bit) */
    emitANDI(b, 0x02);              /* R0 <- R0 & 0x02 (S Bit) */
    emitALU(b, R0, R3, OP_OR);      /* R3 <- R0 | R3 (Put SH2 S Bit in) */
    emitLDC(b, R3, R_SR);           /* SR <- R3 */
    emitMACW(b, R15, R15);          /* Perform the MAC.W */
    emitLDC(b, R2, R_SR);           /* SR <- R2 */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */

    b->cycles += 3;                 /* 3 Cycles */
    b->pc += 2;
}