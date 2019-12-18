#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_7__ {int ea_addr; int fault_addr; int fault_status; void* exception; int /*<<< orphan*/ * A; int /*<<< orphan*/ * D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_MODIFY ; 
 int /*<<< orphan*/  ACCESS_READ ; 
#define  EA_ADDRESS_REG 129 
#define  EA_DATA_REG 128 
 int EA_MODE (int /*<<< orphan*/ ) ; 
 unsigned int EA_REG (int /*<<< orphan*/ ) ; 
 void* EX_ADDRESS_ERROR ; 
 void* EX_ILLEGAL_INSTRUCTION ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_READ ; 
 int /*<<< orphan*/  READU16 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  READU32 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  READU8 (TYPE_1__*,int) ; 
 int SIZE_B ; 
 int SIZE_W ; 
 int ea_resolve (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t ea_get(Q68State *state, uint32_t opcode, int size,
                       int is_rmw, int *cycles_ret)
{
    const unsigned int reg = EA_REG(opcode);
    switch (EA_MODE(opcode)) {
      case EA_DATA_REG:
        *cycles_ret = 0;
        return size==SIZE_B ? (uint8_t) state->D[reg] :
               size==SIZE_W ? (uint16_t)state->D[reg] : state->D[reg];
      case EA_ADDRESS_REG:
        if (size == SIZE_B) {
            /* An.b not permitted */
            state->exception = EX_ILLEGAL_INSTRUCTION;
            *cycles_ret = -1;
            return 0;
        } else {
            *cycles_ret = 0;
            return size==SIZE_W ? (uint16_t)state->A[reg] : state->A[reg];
        }
      default: {
        *cycles_ret = ea_resolve(state, opcode, size,
                                 is_rmw ? ACCESS_MODIFY : ACCESS_READ);
        if (*cycles_ret < 0) {
            state->exception = EX_ILLEGAL_INSTRUCTION;
            return 0;
        }
        if (size == SIZE_B) {
            return READU8(state, state->ea_addr);
        } else {
#ifndef Q68_DISABLE_ADDRESS_ERROR
            if (state->ea_addr & 1) {
                state->exception = EX_ADDRESS_ERROR;
                state->fault_addr = state->ea_addr;
                state->fault_status = FAULT_STATUS_IN_DATA
                                    | FAULT_STATUS_RW_READ;
                *cycles_ret = -1;
                return 0;
            }
#endif
            return size==SIZE_W ? READU16(state, state->ea_addr)
                                : READU32(state, state->ea_addr);
        }
      }
    }
}