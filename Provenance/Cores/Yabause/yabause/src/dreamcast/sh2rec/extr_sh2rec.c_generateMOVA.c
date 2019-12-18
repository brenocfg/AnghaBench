#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int pc; int /*<<< orphan*/  cycles; scalar_t__ ptr; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R2 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emit16 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emit32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitBRA (TYPE_1__*,int) ; 
 int /*<<< orphan*/  emitMOVLI (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void generateMOVA(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);
    uint32_t addr = ((b->pc + 4) & 0xFFFFFFFC) + (imm << 2);

    if(((uint32_t)b->ptr) & 0x03) {
        emitMOVLI(b, 1, R2);        /* R2 <- calculated effective addr */
        emitBRA(b, 2);              /* Jump beyond the constant */
        emitMOVLS4(b, R2, 0, R8);   /* sh2[R0] <- R2 */
        emit32(b, addr);            /* MOVA effective address */
    }
    else {
        emitMOVLI(b, 1, R2);        /* R2 <- calculated effective addr */
        emitBRA(b, 3);              /* Jump beyond the constant */
        emitMOVLS4(b, R2, 0, R8);   /* sh2[R0] <- R2 */
        emit16(b, 0);               /* Padding, for alignment issues */
        emit32(b, addr);            /* MOVA effective address */
    }

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}