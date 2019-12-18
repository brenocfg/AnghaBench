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
typedef  int uint32_t ;
struct TYPE_3__ {int SR; int /*<<< orphan*/  USP; int /*<<< orphan*/ * A; int /*<<< orphan*/  exception; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  EX_PRIVILEGE_VIOLATION ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int SR_S ; 
 size_t reg0 ; 

__attribute__((used)) static int opMUSP(Q68State *state, uint32_t opcode)
{
    if (!(state->SR & SR_S)) {
        state->exception = EX_PRIVILEGE_VIOLATION;
        return 0;
    }

    INSN_GET_REG0;
    if (opcode & 0x0008) {
        state->USP = state->A[reg0];
    } else {
        state->A[reg0] = state->USP;
    }
    return 4;
}