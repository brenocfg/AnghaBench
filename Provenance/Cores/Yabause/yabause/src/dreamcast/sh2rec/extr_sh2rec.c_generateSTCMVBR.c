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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_11__ {int cycles; int pc; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R1 ; 
 int /*<<< orphan*/  R10 ; 
 int /*<<< orphan*/  R4 ; 
 int /*<<< orphan*/  R5 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  R9 ; 
 int /*<<< orphan*/  R_PR ; 
 int /*<<< orphan*/  emitADDI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitJSR (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitLDS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOV (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLLG (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitSTS (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateSTCMVBR(uint16_t inst, sh2rec_block_t *b) {
    int regn = INSTRUCTION_B(inst);

    emitMOVLLG(b, 18);              /* R0 <- sh2[VBR] */
    emitMOVLL4(b, R9, 5, R1);       /* R1 <- MappedMemoryWriteLong */
    emitMOVLL4(b, R8, regn, R4);    /* R4 <- sh2[Rn] */
    emitSTS(b, R_PR, R10);          /* R10 <- PR */
    emitADDI(b, -4, R4);            /* R4 -= 4 */
    emitMOV(b, R0, R5);             /* R5 <- R0 */
    emitJSR(b, R1);                 /* Call MappedMemoryWriteLong */
    emitMOVLS4(b, R4, regn, R8);    /* sh2[Rn] <- R4 */
    emitLDS(b, R10, R_PR);          /* PR <- R10 */

    b->cycles += 2;                 /* 2 Cycles */
    b->pc += 2;
}