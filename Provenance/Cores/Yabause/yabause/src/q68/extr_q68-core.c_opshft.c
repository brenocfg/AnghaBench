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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int int8_t ;
typedef  int int32_t ;
typedef  int int16_t ;
struct TYPE_6__ {int* D; int SR; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_OFS ; 
 scalar_t__ EA_ADDRESS_REG ; 
 scalar_t__ EA_MODE (int) ; 
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_GET_COUNT ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  INSN_GET_SIZE ; 
 int /*<<< orphan*/  INSN_SETNZ (int) ; 
#define  SIZE_B 129 
 int SIZE_L ; 
#define  SIZE_W 128 
 int SR_C ; 
 int SR_V ; 
 int SR_X ; 
 int SR_X_SHIFT ; 
 int /*<<< orphan*/  WORD_OFS ; 
 int count ; 
 int ea_get (TYPE_1__*,int,int,int,int*) ; 
 int /*<<< orphan*/  ea_set (TYPE_1__*,int,int,int) ; 
 int op_ill (TYPE_1__*,int) ; 
 size_t reg ; 
 size_t reg0 ; 
 int size ; 

__attribute__((used)) static int opshft(Q68State *state, uint32_t opcode)
{
    const int is_left = opcode & 0x0100;
    INSN_GET_SIZE;
    INSN_GET_COUNT;
    INSN_GET_REG0;
    int is_memory;
    int type;  // Shift/rotate type (0=ASL/ASR, 1=LSL/LSR, ...)
    uint32_t data;
    int cycles;

    if (size == 3) {
        /* Memory shift/rotate */
        is_memory = 1;
        if ((opcode & 0x0800) || EA_MODE(opcode) <= EA_ADDRESS_REG) {
            return op_ill(state, opcode);
        }
        size = SIZE_W;
        type = opcode>>9 & 3;
        count = 1;
        data = ea_get(state, opcode, size, 1, &cycles);
        if (cycles < 0) {
            return 0;
        }
    } else {
        /* Register shift/rotate */
        is_memory = 0;
        type = opcode>>3 & 3;
        if (opcode & 0x0020) {
            INSN_GET_REG;
            count = state->D[reg] & 63;
        }
        data = size==SIZE_B ? (uint8_t) state->D[reg0] :
               size==SIZE_W ? (uint16_t)state->D[reg0] : state->D[reg0];
        cycles = 0;
    }
    cycles += count*2;

    INSN_CLEAR_CC();
    if (count > 0) {
        const int nbits = (size==SIZE_B ? 8 : size==SIZE_W ? 16 : 32);
        switch (type) {
          case 0:  // ASL/ASR
            state->SR &= ~SR_X;
            if (is_left) {
                int V = 0, C;
                /* Have to shift bit by bit to detect overflow */
                for (; count > 0; count--) {
                    C = (data >> (nbits-1)) & 1;
                    data <<= 1;
                    V |= (C ^ (data >> (nbits-1))) & 1;
                }
                if (V) {
                    state->SR |= SR_V;
                }
                if (C) {
                    state->SR |= SR_X | SR_C;
                }
            } else {
                if (size == SIZE_B) {  // Sign extend if necessary
                    data = (int8_t)data;
                } else if (size == SIZE_W) {
                    data = (int16_t)data;
                }
                if (count > nbits) {
                    count = 32;  // Some systems break with a shift count >32
                }
                data = (int32_t)data >> (count-1);
                if (data & 1) {
                    state->SR |= SR_X | SR_C;
                }
                data = (int32_t)data >> 1;
            }
            break;
          case 1:  // LSL/LSR
            state->SR &= ~SR_X;
            if (count > nbits) {
                data = 0;
            } else if (is_left) {
                data <<= count-1;
                if ((data >> (nbits-1)) & 1) {
                    state->SR |= SR_X | SR_C;
                }
                data <<= 1;
            } else {
                data = (int32_t)data >> (count-1);
                if (data & 1) {
                    state->SR |= SR_X | SR_C;
                }
                data = (int32_t)data >> 1;
            }
            break;
          case 2: {  // ROXL/ROXR
            uint32_t X = (state->SR >> SR_X_SHIFT) & 1;
            state->SR &= ~SR_X;
            if (is_left) {
                for (; count > 0; count--) {
                    const int new_X = (data >> (nbits-1)) & 1;
                    data = (data << 1) | X;
                    X = new_X;
                }
            } else {
                for (; count > 0; count--) {
                    const int new_X = data & 1;
                    data = (data >> 1) | (X << (nbits-1));
                    X = new_X;
                }
            }
            if (X) {
                state->SR |= SR_C | SR_X;
            }
            break;
          }
          default: {  // (case 3) ROL/ROR
            count %= nbits;
            if (is_left) {
                data = (data << count) | (data >> (nbits - count));
                if ((data >> (nbits-1)) & 1) {
                    state->SR |= SR_C;
                }
                data <<= 1;
            } else {
                data = (data >> count) | (data << (nbits - count));
                if (data & 1) {
                    state->SR |= SR_C;
                }
                data = (int32_t)data >> 1;
            }
            break;
          }
        }  // switch (type)
    } else {  // count == 0
        if (type == 2 && (state->SR & SR_X)) {
            state->SR |= SR_C;
        }
    }
    INSN_SETNZ(size==SIZE_B ? (int8_t) data : 
               size==SIZE_W ? (int16_t)data : data);

    if (is_memory) {
        ea_set(state, opcode, size, data);
    } else {
        switch (size) {
          case SIZE_B: *(BYTE_OFS + (uint8_t  *)&state->D[reg0]) = data; break;
          case SIZE_W: *(WORD_OFS + (uint16_t *)&state->D[reg0]) = data; break;
          default:     state->D[reg0] = data;                            break;
        }
    }
    return (size==SIZE_L ? 8 : 6) + cycles;
}