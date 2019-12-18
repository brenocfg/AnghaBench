#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  inst; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_8__ {int imm; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_9__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 int /*<<< orphan*/  MCInst_setOpcode (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* build_init_op (TYPE_1__*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_imm(m68k_info *info, int opcode, int data)
{
	cs_m68k_op* op;
	cs_m68k* ext = build_init_op(info, opcode, 1, 0);

	MCInst_setOpcode(info->inst, opcode);

	op = &ext->operands[0];

	op->type = M68K_OP_IMM;
	op->address_mode = M68K_AM_IMMEDIATE;
	op->imm = data;
}