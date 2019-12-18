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
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ROTCL ; 
 int /*<<< orphan*/  OP_ROTCR ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emitMOV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitSHIFT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitTSTI (TYPE_1__*,int) ; 

__attribute__((used)) static void generateTSTI(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);

    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitMOV(b, R0, R2);             /* R2 <- R0 */
    emitMOVLL4(b, R8, 0, R0);       /* R0 <- sh2[R0] */
    emitSHIFT(b, R2, OP_ROTCR);     /* Rotate SH2's T Bit in place */
    emitTSTI(b, imm);               /* tst #imm, r0 */
    emitSHIFT(b, R2, OP_ROTCL);     /* Rotate T back to SH2 reg */
    emitMOV(b, R2, R0);             /* R0 <- R2 */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}