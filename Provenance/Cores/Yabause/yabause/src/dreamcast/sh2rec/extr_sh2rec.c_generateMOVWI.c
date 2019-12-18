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
struct TYPE_14__ {int pc; int /*<<< orphan*/  cycles; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_EXTSW ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitNOP (TYPE_1__*) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateMOVWI(uint16_t inst, sh2rec_block_t *b) {
    int regn = INSTRUCTION_B(inst);
    int imm = INSTRUCTION_CD(inst);
    uint32_t addr = b->pc + 4 + (imm << 1);

    if(((uint32_t)b->ptr) & 0x03) {
        emitMOVLI(b, 1, R4);        /* R4 <- calculated effective addr */
        emitBRA(b, 2);              /* Jump beyond the constant */
        emitMOVLL4(b, R9, 1, R0);   /* R0 <- MappedMemoryReadWord */
        emit32(b, addr);            /* MOV.W effective address */
    }
    else {
        emitMOVLI(b, 1, R4);        /* R4 <- calculated effective addr */
        emitBRA(b, 3);              /* Jump beyond the constant */
        emitMOVLL4(b, R9, 1, R0);   /* R0 <- MappedMemoryReadWord */
        emit16(b, 0);               /* Padding, for alignment issues */
        emit32(b, addr);            /* MOV.W effective address */
    }

    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitJSR(b, R0);                 /* Call MappedMemoryReadWord */
    emitNOP(b);                     /* XXXX: Nothing to put here */
    emitALU(b, R0, R0, OP_EXTSW);   /* Sign extend read word */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */
    emitMOVLS4(b, R0, regn, R8);    /* sh2[Rn] <- read word */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}