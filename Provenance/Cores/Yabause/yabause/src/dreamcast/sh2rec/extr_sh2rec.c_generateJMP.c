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
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_8__ {int pc; int cycles; } ;
typedef  TYPE_1__ sh2rec_block_t ;

/* Variables and functions */
 int INSTRUCTION_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  R0 ; 
 int /*<<< orphan*/  R15 ; 
 int /*<<< orphan*/  R8 ; 
 int /*<<< orphan*/  emitMOVLL4 (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLM (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitMOVLP (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  emitRTS (TYPE_1__*) ; 
 int /*<<< orphan*/  sh2rec_rec_inst (TYPE_1__*,int) ; 

__attribute__((used)) static void generateJMP(uint16_t inst, sh2rec_block_t *b) {
    int regm = INSTRUCTION_B(inst);

    emitMOVLL4(b, R8, regm, R0);    /* Grab the next PC value */
    emitMOVLM(b, R0, R15);          /* Push the next PC on the stack */

    /* Deal with the delay slot */
    b->pc += 2;
    sh2rec_rec_inst(b, 1);

    emitRTS(b);                     /* Return to sender! */
    emitMOVLP(b, R15, R0);          /* Pop the next PC (delay slot) */

    b->cycles += 2;                 /* 2 Cycles */
}