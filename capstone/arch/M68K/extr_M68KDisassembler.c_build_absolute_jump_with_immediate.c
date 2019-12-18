#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  m68k_info ;
struct TYPE_4__ {int imm; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cs_m68k_op ;
struct TYPE_5__ {TYPE_1__* operands; } ;
typedef  TYPE_2__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 TYPE_2__* build_init_op (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  set_insn_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_absolute_jump_with_immediate(m68k_info *info, int opcode, int size, int immediate)
{
	cs_m68k_op* op;
	cs_m68k* ext = build_init_op(info, opcode, 1, size);

	op = &ext->operands[0];

	op->type = M68K_OP_IMM;
	op->address_mode = M68K_AM_IMMEDIATE;
	op->imm = immediate;

	set_insn_group(info, M68K_GRP_JUMP);
}