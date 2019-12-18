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
typedef  void* uint8_t ;
typedef  void* uint32_t ;
typedef  void* uint16_t ;
typedef  void* int16_t ;
struct TYPE_6__ {int ea_addr; int fault_addr; int fault_status; int /*<<< orphan*/  exception; void** A; void** D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  BYTE_OFS ; 
#define  EA_ADDRESS_REG 131 
#define  EA_DATA_REG 130 
 int EA_MODE (void*) ; 
 unsigned int EA_REG (void*) ; 
 int /*<<< orphan*/  EX_ADDRESS_ERROR ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
#define  SIZE_B 129 
#define  SIZE_W 128 
 int /*<<< orphan*/  WORD_OFS ; 
 int /*<<< orphan*/  WRITE16 (TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  WRITE32 (TYPE_1__*,int,void*) ; 
 int /*<<< orphan*/  WRITE8 (TYPE_1__*,int,void*) ; 

__attribute__((used)) static void ea_set(Q68State *state, uint32_t opcode, int size, uint32_t data)
{
    const unsigned int reg = EA_REG(opcode);
    switch (EA_MODE(opcode)) {
      case EA_DATA_REG:
        switch (size) {
          case SIZE_B: *(BYTE_OFS + (uint8_t  *)&state->D[reg]) = data; break;
          case SIZE_W: *(WORD_OFS + (uint16_t *)&state->D[reg]) = data; break;
          default:     state->D[reg] = data;                            break;
        }
        return;
      case EA_ADDRESS_REG:
        if (size == SIZE_W) {
            state->A[reg] = (int16_t)data;  // Sign-extended for address regs
        } else {  // must be SIZE_L
            state->A[reg] = data;
        }
        return;
      default: {
        if (size == SIZE_B) {
            WRITE8(state, state->ea_addr, data);
        } else {
#ifndef Q68_DISABLE_ADDRESS_ERROR
            if (state->ea_addr & 1) {
                state->exception = EX_ADDRESS_ERROR;
                state->fault_addr = state->ea_addr;
                state->fault_status = FAULT_STATUS_IN_DATA
                                    | FAULT_STATUS_RW_WRITE;
                return;
            } else
#endif
            if (size == SIZE_W) {
                WRITE16(state, state->ea_addr, data);
            } else {
                WRITE32(state, state->ea_addr, data);
            }
        }
        return;
      }
    }
}