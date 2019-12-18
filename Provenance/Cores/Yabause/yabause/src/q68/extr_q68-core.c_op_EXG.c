#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_4__ {int* D; int* A; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int op_ill (TYPE_1__*,int) ; 
 size_t reg ; 
 size_t reg0 ; 

__attribute__((used)) static int op_EXG(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_REG0;
    const int mode = opcode & 0xF8;

    if (mode == 0x40) {
        const uint32_t tmp = state->D[reg];
        state->D[reg] = state->D[reg0];
        state->D[reg0] = tmp;
    } else if (mode == 0x48) {
        const uint32_t tmp = state->A[reg];
        state->A[reg] = state->A[reg0];
        state->A[reg0] = tmp;
    } else if (mode == 0x88) {
        const uint32_t tmp = state->D[reg];
        state->D[reg] = state->A[reg0];
        state->A[reg0] = tmp;
    } else {
        return op_ill(state, opcode);
    }
    return 6;
}