#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_10__ {int pc; int /*<<< orphan*/  cycles; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_MACL ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateLDSMMACL(uint16_t inst, sh2rec_block_t *b) {
    int regm = INSTRUCTION_B(inst);

    emitMOVLL4(b, R9, 2, R0);       /* R0 <- MappedMemoryReadLong */
    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitMOVLL4(b, R8, regm, R4);    /* R4 <- sh2[Rm] */
    emitMOVI(b, 4, R1);             /* R1 <- 4 */
    emitALU(b, R4, R1, OP_ADD);     /* R1 <- R4 + R1 */
    emitJSR(b, R0);                 /* Call MappedMemoryReadLong */
    emitMOVLS4(b, R1, regm, R8);    /* sh2[Rm] <- R1 */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */
    emitLDS(b, R0, R_MACL);         /* MACL <- R0 */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}