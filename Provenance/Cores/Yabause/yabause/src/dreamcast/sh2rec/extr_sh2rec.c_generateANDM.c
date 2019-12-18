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
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitANDI (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateANDM(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);

    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitMOVLLG(b, 17);              /* R0 <- sh2[GBR] */
    emitMOVLL4(b, R8, 0, R4);       /* R4 <- sh2[R0] */
    emitMOVLL4(b, R9, 0, R1);       /* R1 <- MappedMemoryReadByte */
    emitALU(b, R0, R4, OP_ADD);     /* R4 <- R4 + R0 */
    emitJSR(b, R1);                 /* Call MappedMemoryReadByte */
    emitMOVLM(b, R4, R15);          /* Push R4 on the stack (delay slot) */
    emitMOVLL4(b, R9, 3, R1);       /* R1 <- MappedMemoryWriteByte */
    emitANDI(b, imm);               /* R0 <- R0 & #imm */
    emitMOVLP(b, R15, R4);          /* Pop R4 off the stack */
    emitJSR(b, R1);                 /* Call MappedMemoryWriteByte */
    emitMOV(b, R0, R5);             /* R5 <- R0 (delay slot) */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */

    b->cycles += 3;                 /* 3 Cycles */
    b->pc += 2;
}