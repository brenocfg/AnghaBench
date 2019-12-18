#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int* D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_SETNZ (int) ; 
 size_t reg0 ; 

__attribute__((used)) static int opSWAP(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG0;
    state->D[reg0] = state->D[reg0]>>16 | state->D[reg0]<<16;
    INSN_CLEAR_CC();
    INSN_SETNZ(state->D[reg0]);
    return 4;
}