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
struct TYPE_18__ {int pc; int cycles; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_AND ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVWI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh2rec_rec_inst (TYPE_1__*,int) ; 

__attribute__((used)) static void generateRTE(uint16_t inst, sh2rec_block_t *b) {
    emitMOVLL4(b, R9, 2, R0);       /* R0 <- MappedMemoryReadLong */
    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitJSR(b, R0);                 /* Call MappedMemoryReadLong */
    emitMOVLL4(b, R8, 15, R4);      /* R4 <- sh2[R15] (delay slot) */
    emitMOVLL4(b, R9, 2, R1);       /* R1 <- MappedMemoryReadLong */
    emitMOVLL4(b, R8, 15, R4);      /* R4 <- sh2[R15] */
    emitMOVI(b, 4, R2);             /* R2 <- 4 */
    emitALU(b, R2, R4, OP_ADD);     /* R4 <- R4 + R2 */
    emitMOVLM(b, R0, R15);          /* Push the next PC */
    emitALU(b, R4, R2, OP_ADD);     /* R2 <- R4 + R2 */
    emitJSR(b, R1);                 /* Call MappedMemoryReadLong */
    emitMOVLS4(b, R2, 15, R8);      /* sh2[R15] <- R2 (delay slot) */
    emitMOVWI(b, 1, R1);            /* R1 <- 0x000003F3 */
    emitBRA(b, 1);                  /* Branch around the constant */
    emitALU(b, R1, R0, OP_AND);     /* R0 <- R0 & R1 */
    emit16(b, 0x03F3);              /* Mask for SR register */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */

    /* Deal with the delay slot */
    b->pc += 2;
    sh2rec_rec_inst(b, 1);

    emitRTS(b);                     /* Return to sender! */
    emitMOVLP(b, R15, R0);          /* Pop the next PC (delay slot) */

    b->cycles += 4;                 /* 4 Cycles */
}