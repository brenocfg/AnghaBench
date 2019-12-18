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
typedef  int /*<<< orphan*/  Q68State ;

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
 int FAULT_STATUS_IN_DATA ; 
 int FAULT_STATUS_RW_WRITE ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_CHECK_ALIGNED_SP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  JIT_EMIT_JMP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JIT_EMIT_JSR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIZE_W ; 
 int /*<<< orphan*/  advance_PC (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  current_entry ; 
 int /*<<< orphan*/  ea_resolve (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jit_PC ; 
 int op_ill (int /*<<< orphan*/ *,int) ; 

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
    if (is_jsr) {
        cycles += 8;
    }
    JIT_EMIT_ADD_CYCLES(current_entry, cycles);
    advance_PC(state);

    ea_resolve(state, opcode, SIZE_W, ACCESS_READ);  // cannot fail
    if (is_jsr) {
#ifndef Q68_DISABLE_ADDRESS_ERROR
        JIT_EMIT_CHECK_ALIGNED_SP(current_entry, opcode,
                                  FAULT_STATUS_IN_DATA | FAULT_STATUS_RW_WRITE);
#endif
        JIT_EMIT_JSR(current_entry, jit_PC);
        return 0;
    } else {
        JIT_EMIT_JMP(current_entry);
        return 1;
    }
}