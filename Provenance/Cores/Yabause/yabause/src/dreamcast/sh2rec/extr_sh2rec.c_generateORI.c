#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_6__ {int pc; int /*<<< orphan*/  cycles; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_CD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLS4 (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitORI (TYPE_1__*,int) ; 

__attribute__((used)) static void generateORI(uint16_t inst, sh2rec_block_t *b) {
    int imm = INSTRUCTION_CD(inst);

    emitMOVLL4(b, R8, 0, R0);       /* R0 <- sh2[R0] */
    emitORI(b, imm);                /* R0 <- R0 | #imm */
    emitMOVLS4(b, R0, 0, R8);       /* sh2[R0] <- R0 */

    ++b->cycles;                    /* 1 Cycle */
    b->pc += 2;
}