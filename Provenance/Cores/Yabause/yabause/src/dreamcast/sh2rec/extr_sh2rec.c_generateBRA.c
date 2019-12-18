#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int cycles; scalar_t__ pc; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;
typedef  scalar_t__ int32_t ;

/* Variables and functions */
 int INSTRUCTION_BCD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  sh2rec_rec_inst (TYPE_1__*,int) ; 

__attribute__((used)) static void generateBRA(uint16_t inst, sh2rec_block_t *b) {
    int disp = INSTRUCTION_BCD(inst);
    int32_t val;

    if(disp & 0x00000800) {
        disp |= 0xFFFFF000;
    }

    val = b->pc + 4 + (disp << 1);

    emitMOVLI(b, 1, R2);            /* R2 <- sh2[PC] + 4 + disp */

    if(((uint32_t)b->ptr) & 0x03) {
        emitBRA(b, 3);              /* Branch around the constant */
        emitMOVLM(b, R2, R15);      /* Push the next PC (delay slot) */
        emit16(b, 0);               /* Padding since we need it */
    }
    else {
        emitBRA(b, 2);              /* Branch around the constant */
        emitMOVLM(b, R2, R15);      /* Push the next PC (delay slot) */
    }

    emit32(b, (uint32_t )val);      /* The next PC */

    /* Deal with the delay slot */
    b->pc += 2;
    sh2rec_rec_inst(b, 1);

    emitRTS(b);                     /* Return to sender! */
    emitMOVLP(b, R15, R0);          /* Pop the next PC (delay slot) */

    b->cycles += 2;                 /* 2 Cycles */
}