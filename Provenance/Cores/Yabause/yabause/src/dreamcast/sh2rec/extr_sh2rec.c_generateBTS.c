#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_16__ {int pc; int /*<<< orphan*/  cycles; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_ROTCR ; 
 int /*<<< orphan*/  OP_SHLL ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitBF (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  emitSHIFT (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2rec_rec_inst (TYPE_1__*,int) ; 

__attribute__((used)) static void generateBTS(uint16_t inst, sh2rec_block_t *b) {
    int disp = INSTRUCTION_CD(inst);
    uint32_t val = b->pc + 4;
    int n = (((uint32_t)b->ptr) & 0x03) ? 3 : 4;

    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitMOVLI(b, n, R2);            /* R2 <- sh2[PC] + 2 */
    emitSHIFT(b, R0, OP_ROTCR);     /* Rotate SH2's T Bit in place */
    emitMOVI(b, 0, R0);             /* R0 <- 0 */
    emitBF(b, 1);                   /* Branch around the addition if needed */
    emitMOVI(b, disp, R0);          /* R0 <- displacement */
    emitSHIFT(b, R0, OP_SHLL);      /* R0 <- R0 << 1 */

    if(((uint32_t)b->ptr) & 0x03) {
        emitBRA(b, 3);              /* Branch around the constant */
        emitALU(b, R2, R0, OP_ADD); /* R0 <- R0 + R2 (delay slot) */
        emit16(b, 0);               /* Padding since we need it */
    }
    else {
        emitBRA(b, 2);              /* Branch around the constant */
        emitALU(b, R2, R0, OP_ADD); /* R0 <- R0 + R2 (delay slot) */
    }

    emit32(b, val);                 /* The next PC value (if not taken) */
    emitMOVLM(b, R0, R15);          /* Push the next PC */

    /* Deal with the delay slot */
    b->pc += 2;
    sh2rec_rec_inst(b, 1);

    emitRTS(b);                     /* Return to sender! */
    emitMOVLP(b, R15, R0);          /* Pop the next PC (delay slot) */

    ++b->cycles;                    /* 1 Cycle (if not taken) */
    /* XXXX: Handle taken case cycle difference */
}