#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int SR; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int EA_DATA_REG ; 
 int EA_PREDECREMENT ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 scalar_t__ SIZE_L ; 
 int SIZE_TO_BYTES (scalar_t__) ; 
 int SR_C ; 
 int SR_N ; 
 int SR_V ; 
 int SR_X ; 
 int SR_X_SHIFT ; 
 int SR_Z ; 
 int ea_get (TYPE_1__*,int const,scalar_t__,int,int*) ; 
 int /*<<< orphan*/  ea_set (TYPE_1__*,int const,scalar_t__,int) ; 
 int reg ; 
 int reg0 ; 
 scalar_t__ size ; 

__attribute__((used)) static int opADSX(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_SIZE;
    INSN_GET_REG0;
    const int is_add = opcode & 0x4000;
    const int is_memory = opcode & 0x0008;
    const int bytes = SIZE_TO_BYTES(size);
    const int shift = bytes*8 - 1;
    const uint32_t valuemask = ~(~1 << shift);

    const uint16_t src_ea =
        (is_memory ? EA_PREDECREMENT : EA_DATA_REG) << 3 | reg0;
    const uint16_t dest_ea =
        (is_memory ? EA_PREDECREMENT : EA_DATA_REG) << 3 | reg;
    int dummy;
    uint32_t src  = ea_get(state, src_ea,  size, 0, &dummy);
    uint32_t dest = ea_get(state, dest_ea, size, 1, &dummy);

    uint32_t result;
    int X = (state->SR >> SR_X_SHIFT) & 1;
    state->SR &= ~(SR_X | SR_N | SR_V | SR_C);  // Z is never set, only cleared
    if (is_add) {
        result = (dest + src + X) & valuemask;
        if (((src ^ result) & (dest ^ result)) >> shift) {
            state->SR |= SR_V;
        }
        if ((int)((src >> shift) + (dest >> shift) - (result >> shift)) > 0) {
            state->SR |= SR_X | SR_C;
        }
    } else {
        result = (dest - src - X) & valuemask;
        if (((src ^ dest) & (result ^ dest)) >> shift) {
            state->SR |= SR_V;
        }
        if ((int)((src >> shift) - (dest >> shift) + (result >> shift)) > 0) {
            state->SR |= SR_X | SR_C;
        }
    }
    if (result >> shift) {
        state->SR |= SR_N;
    }
    if (result != 0) {
        state->SR &= ~SR_Z;
    }

    ea_set(state, dest_ea, size, result);
    return (is_memory ? (size==SIZE_L ? 30 : 18) : (size==SIZE_L ? 8 : 4));
}