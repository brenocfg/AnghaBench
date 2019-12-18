#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_3__ {int /*<<< orphan*/ * D; } ;
typedef  TYPE_1__ Q68State ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_CLEAR_CC () ; 
 int /*<<< orphan*/  INSN_GET_IMM8 ; 
 int /*<<< orphan*/  INSN_GET_REG ; 
 int /*<<< orphan*/  INSN_SETNZ (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  imm8 ; 
 size_t reg ; 

__attribute__((used)) static int opMOVQ(Q68State *state, uint32_t opcode)
{
    INSN_GET_REG;
    INSN_GET_IMM8;
    state->D[reg] = imm8;
    INSN_CLEAR_CC();
    INSN_SETNZ(imm8);
    return 4;
}