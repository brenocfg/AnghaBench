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
 int /*<<< orphan*/  OP_AND ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLSG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVWI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateLDCSR(uint16_t inst, sh2rec_block_t *b) {
    int regm = INSTRUCTION_B(inst);

    emitMOVWI(b, 2, R2);            /* R2 <- 0x03F3 */
    emitMOVLL4(b, R8, regm, R0);    /* R0 <- sh2[Rm] */
    emitBRA(b, 1);                  /* Jump beyond the constant */
    emitALU(b, R2, R0, OP_AND);     /* R0 <- R0 & R2 (delay slot) */
    emit16(b, 0x03F3);              /* 0x03F3, grabbed by the emitMOVWI */
    emitMOVLSG(b, 16);              /* sh2[SR] <- R0 */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}