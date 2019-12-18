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
typedef  unsigned int const uint16_t ;
typedef  int int16_t ;
struct TYPE_4__ {int* D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_SETNZ (unsigned int) ; 
 int /*<<< orphan*/  SIZE_W ; 
 unsigned int ea_get (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 size_t reg ; 

__attribute__((used)) static int op_MUL(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    const int sign = opcode & (1<<8);

    int cycles;
    const uint16_t data = ea_get(state, opcode, SIZE_W, 0, &cycles);
    if (cycles < 0) {
        return 0;
    }

    if (sign) {
        state->D[reg] = (int16_t)state->D[reg] * (int16_t)data;
    } else {
        state->D[reg] = (uint16_t)state->D[reg] * data;
    }
    INSN_CLEAR_CC();
    INSN_SETNZ(state->D[reg]);

    /* Precise timing varies with the effective address; the algorithm is
     * implemented below for reference, but for typical usage it's probably
     * not important to be exact */
#ifdef MUL_PRECISE_TIMING  // not normally defined
    if (sign) {
        uint32_t temp;
        for (temp = (uint32_t)data << 1; temp != 0; temp >>= 1) {
            if ((temp & 3) == 1 || (temp & 3) == 2) {
                cycles += 2;
            }
        }
    } else {
        unsigned int temp;
        for (temp = data; temp != 0; temp >>= 1) {
            if (temp & 1) {
                cycles += 2;
            }
        }
    }
    return 38 + cycles;
#else  // !MUL_PRECISE_TIMING
    return 54 + cycles;
#endif
}