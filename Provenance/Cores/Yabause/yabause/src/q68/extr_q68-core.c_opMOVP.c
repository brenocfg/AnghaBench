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
typedef  int uint32_t ;
typedef  int int16_t ;
struct TYPE_6__ {int* A; int* D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int IFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int READU8 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  WRITE8 (TYPE_1__*,int,int) ; 
 size_t reg ; 
 size_t reg0 ; 

__attribute__((used)) static int opMOVP(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_REG0;
    int to_memory = opcode & 0x0080;
    int is_long   = opcode & 0x0040;
    int16_t disp  = IFETCH(state);
    uint32_t addr = state->A[reg0] + disp;

    if (to_memory) {
        uint32_t data = state->D[reg];
        if (is_long) {
            WRITE8(state, addr+0, data>>24);
            WRITE8(state, addr+2, data>>16);
            WRITE8(state, addr+4, data>> 8);
            WRITE8(state, addr+6, data>> 0);
        } else {
            WRITE8(state, addr+0, data>> 8);
            WRITE8(state, addr+2, data>> 0);
        }
    } else {
        uint32_t data;
        if (is_long) {
            data  = READU8(state, addr+0) << 24;
            data |= READU8(state, addr+2) << 16;
            data |= READU8(state, addr+4) <<  8;
            data |= READU8(state, addr+6) <<  0;
        } else {
            data  = READU8(state, addr+0) <<  8;
            data |= READU8(state, addr+2) <<  0;
        }
        state->D[reg] = data;
    }

    return is_long ? 24 : 16;
}