#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_19__ {int pc; int cycles; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  OP_ADD ; 
 int /*<<< orphan*/  OP_EXTUB ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitADDI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitALU (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitNOP (TYPE_1__*) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  emitSHLL2 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateTRAPA(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);
    int disp = (((uint32_t)(b->ptr)) & 0x03) ? 5 : 6;
    uint32_t val = b->pc + 2;

    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitMOVLL4(b, R8, 15, R4);      /* R4 <- sh2[R15] */
    emitMOVLL4(b, R9, 5, R1);       /* R1 <- MemoryMappedWriteLong */
    emitMOVLLG(b, 16);              /* R0 <- sh2[SR] */
    emitADDI(b, -4, R4);            /* R4 <- R4 - 4 */
    emitJSR(b, R1);                 /* Call MemoryMappedWriteLong */
    emitMOV(b, R0, R5);             /* R5 <- R0 (delay slot) */
    emitMOVLL4(b, R8, 15, R4);      /* R4 <- sh2[R15] */
    emitMOVLL4(b, R9, 5, R1);       /* R1 <- MemoryMappedWriteLong */
    emitADDI(b, -8, R4);            /* R4 <- R4 - 8 */
    emitMOVLI(b, disp, R5);         /* R5 <- Updated PC value (to be stacked) */
    emitJSR(b, R1);                 /* Call MemoryMappedWriteLong */
    emitMOVLS4(b, R4, 15, R8);      /* sh2[R15] <- R4 (delay slot) */
    emitMOVI(b, imm, R4);           /* R4 <- immediate data */
    emitALU(b, R4, R4, OP_EXTUB);   /* Zero-extend R4 */
    emitMOVLL4(b, R9, 2, R1);       /* R1 <- MemoryMappedReadLong */
    emitMOVLLG(b, 18);              /* R0 <- sh2[VBR] */
    emitSHLL2(b, R4);               /* R4 <- R4 << 2 */
    emitJSR(b, R1);                 /* Call MemoryMappedReadLong */
    emitALU(b, R0, R4, OP_ADD);     /* R4 <- R4 + R0 (delay slot) */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */
    emitRTS(b);                     /* Return to sender! */
    emitNOP(b);                     /* XXXX: Nothing here */
    if(((uint32_t)b->ptr) & 0x03)
        emit16(b, 0);               /* Padding for the alignment */
    emit32(b, val);                 /* The PC value to be loaded by the MOVLI */
    
    b->cycles += 8;                 /* 8 Cycles */
}