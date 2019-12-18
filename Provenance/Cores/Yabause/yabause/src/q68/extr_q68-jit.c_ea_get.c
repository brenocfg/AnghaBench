#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint32_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  ACCESS_MODIFY ; 
 int /*<<< orphan*/  ACCESS_READ ; 
#define  EA_ADDRESS_REG 130 
#define  EA_DATA_REG 129 
#define  EA_MISC 128 
 int EA_MISC_IMMEDIATE ; 
 int EA_MODE (int) ; 
 int EA_REG (int) ; 
 int /*<<< orphan*/  EX_ILLEGAL_INSTRUCTION ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_READ ; 
 int IFETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_EA (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_EA_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_EA_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_EA_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_IMMEDIATE (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP1_REGISTER (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_EA_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_EA_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_EA_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_GET_OP2_REGISTER (int /*<<< orphan*/ ,int) ; 
 int SIZE_B ; 
 int SIZE_L ; 
 int SIZE_W ; 
 int /*<<< orphan*/  current_entry ; 
 int ea_resolve (int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ea_get(Q68State *state, uint32_t opcode, int size,
                   int is_rmw, int *cycles_ret, int op_num)
{
    switch (EA_MODE(opcode)) {

      case EA_DATA_REG:
        *cycles_ret = 0;
        if (op_num == 1) {
            JIT_EMIT_GET_OP1_REGISTER(current_entry, EA_REG(opcode) * 4);
        } else {
            JIT_EMIT_GET_OP2_REGISTER(current_entry, EA_REG(opcode) * 4);
        }
        break;

      case EA_ADDRESS_REG:
        *cycles_ret = 0;
        if (size == SIZE_B) {
            /* An.b not permitted */
            raise_exception(state, EX_ILLEGAL_INSTRUCTION);
            *cycles_ret = -1;
            return;
        } else {
            if (op_num == 1) {
                JIT_EMIT_GET_OP1_REGISTER(current_entry,
                                          (8 + EA_REG(opcode)) * 4);
            } else {
                JIT_EMIT_GET_OP2_REGISTER(current_entry,
                                          (8 + EA_REG(opcode)) * 4);
            }
        }
        break;

      case EA_MISC:
        if (EA_REG(opcode) == EA_MISC_IMMEDIATE) {
            if (is_rmw) {
                raise_exception(state, EX_ILLEGAL_INSTRUCTION);
                *cycles_ret = -1;
                return;
            } else {
                *cycles_ret = (size==SIZE_L ? 8 : 4);
                uint32_t val;
                val = IFETCH(state);
                if (size == SIZE_B) {
                    val &= 0xFF;
                } else if (size == SIZE_L) {
                    val <<= 16;
                    val |= (uint16_t)IFETCH(state);
                }
                if (op_num == 1) {
                    JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, val);
                } else {
                    JIT_EMIT_GET_OP1_IMMEDIATE(current_entry, val);
                }
            }
            break;
        }
        /* else fall through */

      default:
        *cycles_ret = ea_resolve(state, opcode, size,
                                 is_rmw ? ACCESS_MODIFY : ACCESS_READ);
        if (*cycles_ret < 0) {
            raise_exception(state, EX_ILLEGAL_INSTRUCTION);
            return;
        }
        if (size == SIZE_B) {
            if (op_num == 1) {
                JIT_EMIT_GET_OP1_EA_B(current_entry);
            } else {
                JIT_EMIT_GET_OP2_EA_B(current_entry);
            }
        } else if (size == SIZE_W) {
#ifndef Q68_DISABLE_ADDRESS_ERROR
            JIT_EMIT_CHECK_ALIGNED_EA(
                current_entry, opcode,
                FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_READ
            );
#endif
            if (op_num == 1) {
                JIT_EMIT_GET_OP1_EA_W(current_entry);
            } else {
                JIT_EMIT_GET_OP2_EA_W(current_entry);
            }
        } else {  // size == SIZE_L
#ifndef Q68_DISABLE_ADDRESS_ERROR
            JIT_EMIT_CHECK_ALIGNED_EA(
                current_entry, opcode,
                FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_READ
            );
#endif
            if (op_num == 1) {
                JIT_EMIT_GET_OP1_EA_L(current_entry);
            } else {
                JIT_EMIT_GET_OP2_EA_L(current_entry);
            }
        }
        break;

    }  // switch (EA_MODE(opcode))
}