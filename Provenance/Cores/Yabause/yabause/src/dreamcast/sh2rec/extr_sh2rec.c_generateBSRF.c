#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_14__ {int pc; int cycles; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  sh2rec_rec_inst (TYPE_1__*,int) ; 

__attribute__((used)) static void generateBSRF(uint16_t inst, sh2rec_block_t *b) {
    int regm = INSTRUCTION_B(inst);
    uint32_t val = b->pc + 4;

    emitMOVLI(b, 1, R0);            /* R0 <- sh2[PC] + 4 */

    if(((uint32_t)b->ptr) & 0x03) {
        emitBRA(b, 3);              /* Branch around the constant */
        emitMOVLL4(b, R8, regm, R2);/* R2 <- sh2[Rm] (delay slot) */
        emit16(b, 0);               /* Padding since we need it */
    }
    else {
        emitBRA(b, 2);              /* Branch around the constant */
        emitMOVLL4(b, R8, regm, R2);/* R2 <- sh2[Rm] (delay slot) */
    }

    emit32(b, val);                 /* The value to put in PR */
    emitALU(b, R0, R2, OP_ADD);     /* R2 <- R0 + R2 (branch target) */
    emitMOVLSG(b, 21);              /* sh2[PR] <- R0 */
    emitMOVLM(b, R2, R15);          /* Push the next PC */

    /* Deal with the delay slot */
    b->pc += 2;
    sh2rec_rec_inst(b, 1);

    emitRTS(b);                     /* Return to sender! */
    emitMOVLP(b, R15, R0);          /* Pop the next PC (delay slot) */

    b->cycles += 2;                 /* 2 Cycles */
}