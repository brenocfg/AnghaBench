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
typedef  int const uint32_t ;
typedef  int uint16_t ;
struct TYPE_4__ {int /*<<< orphan*/  SR; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int EA_POSTINCREMENT ; 
 int /*<<< orphan*/  INSN_CLEAR_XCC () ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  INSN_SETNZ_SHIFT (int const) ; 
 scalar_t__ SIZE_L ; 
 int SIZE_TO_BYTES (scalar_t__) ; 
 int /*<<< orphan*/  SR_C ; 
 int /*<<< orphan*/  SR_V ; 
 int ea_get (TYPE_1__*,int const,scalar_t__,int /*<<< orphan*/ ,int*) ; 
 int reg ; 
 int reg0 ; 
 scalar_t__ size ; 

__attribute__((used)) static int opCMPM(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_SIZE;
    INSN_GET_REG0;
    const int bytes = SIZE_TO_BYTES(size);
    const int shift = bytes*8 - 1;
    const uint32_t valuemask = ~(~1 << shift);

    const uint16_t src_ea  = EA_POSTINCREMENT<<3 | reg0;
    const uint16_t dest_ea = EA_POSTINCREMENT<<3 | reg;
    int dummy;
    uint32_t src  = ea_get(state, src_ea,  size, 0, &dummy);
    uint32_t dest = ea_get(state, dest_ea, size, 0, &dummy);

    uint32_t result = (dest - src) & valuemask;
    INSN_CLEAR_XCC();
    INSN_SETNZ_SHIFT(result);
    if (((src ^ dest) & (result ^ dest)) >> shift) {
        state->SR |= SR_V;
    }
    if ((int)((src >> shift) - (dest >> shift) + (result >> shift)) > 0) {
        state->SR |= SR_C;
    }

    return size==SIZE_L ? 20 : 12;
}