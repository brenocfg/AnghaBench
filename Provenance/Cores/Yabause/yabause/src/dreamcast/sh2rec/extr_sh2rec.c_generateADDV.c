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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {int pc; int /*<<< orphan*/  cycles; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int INSTRUCTION_C (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ROTCL ; 
 int /*<<< orphan*/  OP_ROTCR ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R3 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emitADDV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitSHIFT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateADDV(uint16_t inst, sh2rec_block_t *b) {
    int regn = INSTRUCTION_B(inst);
    int regm = INSTRUCTION_C(inst);

    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitMOVLL4(b, R8, regn, R2);    /* R2 <- sh2[Rn] */
    emitMOVLL4(b, R8, regm, R3);    /* R3 <- sh2[Rm] */
    emitSHIFT(b, R0, OP_ROTCR);     /* Rotate SH2's T Bit in place */
    emitADDV(b, R3, R2);            /* R2 = R2 + R3 (overflow to T Bit) */
    emitSHIFT(b, R0, OP_ROTCL);     /* Rotate T back to SH2 reg */
    emitMOVLS4(b, R2, regn, R8);    /* sh2[Rn] <- R2 */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}