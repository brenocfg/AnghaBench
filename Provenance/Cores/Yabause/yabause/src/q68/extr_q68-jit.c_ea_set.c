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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
#define  EA_ADDRESS_REG 129 
#define  EA_DATA_REG 128 
 int EA_MODE (int /*<<< orphan*/ ) ; 
 int EA_REG (int /*<<< orphan*/ ) ; 
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_EA (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_AREG_W (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_EA_B (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_EA_L (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_EA_W (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_B (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_L (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_SET_REGISTER_W (int /*<<< orphan*/ ,int) ; 
 int SIZE_B ; 
 int SIZE_W ; 
 int /*<<< orphan*/  current_entry ; 

__attribute__((used)) static void ea_set(Q68State *state, uint32_t opcode, int size)
{
    switch (EA_MODE(opcode)) {
      case EA_DATA_REG:
        if (size == SIZE_B) {
            JIT_EMIT_SET_REGISTER_B(current_entry, EA_REG(opcode) * 4);
        } else if (size == SIZE_W) {
            JIT_EMIT_SET_REGISTER_W(current_entry, EA_REG(opcode) * 4);
        } else {  // size == SIZE_L
            JIT_EMIT_SET_REGISTER_L(current_entry, EA_REG(opcode) * 4);
        }
        return;
      case EA_ADDRESS_REG:
        if (size == SIZE_W) {
            JIT_EMIT_SET_AREG_W(current_entry, (8 + EA_REG(opcode)) * 4);
        } else {  // size == SIZE_L
            JIT_EMIT_SET_REGISTER_L(current_entry, (8 + EA_REG(opcode)) * 4);
        }
        return;
      default: {
        if (size == SIZE_B) {
            JIT_EMIT_SET_EA_B(current_entry);
        } else if (size == SIZE_W) {
#ifndef Q68_DISABLE_ADDRESS_ERROR
            JIT_EMIT_CHECK_ALIGNED_EA(
                current_entry, opcode,
                FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE
            );
#endif
            JIT_EMIT_SET_EA_W(current_entry);
        } else {  // size == SIZE_L
#ifndef Q68_DISABLE_ADDRESS_ERROR
            JIT_EMIT_CHECK_ALIGNED_EA(
                current_entry, opcode,
                FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE
            );
#endif
            JIT_EMIT_SET_EA_L(current_entry);
        }
        return;
      }
    }
}