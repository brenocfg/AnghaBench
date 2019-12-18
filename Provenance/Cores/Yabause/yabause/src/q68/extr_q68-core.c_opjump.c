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
struct TYPE_6__ {int* A; int fault_addr; int fault_status; int /*<<< orphan*/  ea_addr; int /*<<< orphan*/  PC; int /*<<< orphan*/  exception; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_READ ; 
#define  EA_DISPLACEMENT 135 
#define  EA_INDEX 134 
#define  EA_INDIRECT 133 
#define  EA_MISC 132 
#define  EA_MISC_ABSOLUTE_L 131 
#define  EA_MISC_ABSOLUTE_W 130 
#define  EA_MISC_PCREL 129 
#define  EA_MISC_PCREL_INDEX 128 
 int EA_MODE (int) ; 
 int /*<<< orphan*/  EA_REG (int) ; 
 int /*<<< orphan*/  EX_ADDRESS_ERROR ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 int /*<<< orphan*/  PUSH32 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_W ; 
 int /*<<< orphan*/  ea_resolve (TYPE_1__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int op_ill (TYPE_1__*,int) ; 

__attribute__((used)) static int opjump(Q68State *state, uint32_t opcode)
{
    int is_jsr = ~opcode & 0x0040;

    /* JMP is essentially identical to LEA PC,<ea> and has the same
     * constraints.  JSR is equivalent to MOVE.L PC,-(A7) followed by a
     * JMP to the address.  Both use a separate timing table, however. */

    int cycles;
    switch (EA_MODE(opcode)) {
      case EA_INDIRECT:
        cycles = 8;
        break;
      case EA_DISPLACEMENT:
        cycles = 10;
        break;
      case EA_INDEX:
        cycles = 14;
        break;
      case EA_MISC:
        switch (EA_REG(opcode)) {
          case EA_MISC_ABSOLUTE_W:
            cycles = 10;
            break;
          case EA_MISC_ABSOLUTE_L:
            cycles = 12;
            break;
          case EA_MISC_PCREL:
            cycles = 10;
            break;
          case EA_MISC_PCREL_INDEX:
            cycles = 14;
            break;
          default:
            return op_ill(state, opcode);
        }
        break;
      default:
        return op_ill(state, opcode);
    }

    ea_resolve(state, opcode, SIZE_W, ACCESS_READ);  // cannot fail
    if (is_jsr) {
#ifndef Q68_DISABLE_ADDRESS_ERROR
        if (state->A[7] & 1) {
            state->exception = EX_ADDRESS_ERROR;
            state->fault_addr = state->A[7];
            state->fault_status = FAULT_STATUS_IN_DATA
                                | FAULT_STATUS_RW_WRITE;
            return 0;
        }
#endif
        cycles += 8;
        PUSH32(state, state->PC);
    }
    state->PC = state->ea_addr;
    return cycles;
}