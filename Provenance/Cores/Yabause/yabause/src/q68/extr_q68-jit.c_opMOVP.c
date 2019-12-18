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
typedef  int /*<<< orphan*/  int16_t ;
typedef  int /*<<< orphan*/  Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  IFETCH (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_GET_REG0 ; 
 int /*<<< orphan*/  JIT_EMIT_ADD_CYCLES (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVEP_READ_L (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVEP_READ_W (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVEP_WRITE_L (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  JIT_EMIT_MOVEP_WRITE_W (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  current_entry ; 
 int reg ; 
 int reg0 ; 

__attribute__((used)) static int opMOVP(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_REG0;
    int to_memory = opcode & 0x0080;
    int is_long   = opcode & 0x0040;
    int16_t disp  = IFETCH(state);

    if (to_memory) {
        if (is_long) {
            JIT_EMIT_MOVEP_WRITE_L(current_entry, reg0*4, disp, reg*4);
        } else {
            JIT_EMIT_MOVEP_WRITE_W(current_entry, reg0*4, disp, reg*4);
        }
    } else {
        if (is_long) {
            JIT_EMIT_MOVEP_READ_L(current_entry, reg0*4, disp, reg*4);
        } else {
            JIT_EMIT_MOVEP_READ_W(current_entry, reg0*4, disp, reg*4);
        }
    }

    JIT_EMIT_ADD_CYCLES(current_entry, is_long ? 24 : 16);
    return 0;
}