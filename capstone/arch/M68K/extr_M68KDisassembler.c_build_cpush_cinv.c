#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int ir; int /*<<< orphan*/  inst; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_9__ {int imm; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_10__ {int op_count; TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_AM_REG_DIRECT_ADDR ; 
 int /*<<< orphan*/  M68K_INS_INVALID ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 int /*<<< orphan*/  M68K_OP_MEM ; 
 int M68K_REG_A0 ; 
 int /*<<< orphan*/  MCInst_setOpcode (int /*<<< orphan*/ ,int) ; 
 TYPE_3__* build_init_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  d68000_invalid (TYPE_1__*) ; 

__attribute__((used)) static void build_cpush_cinv(m68k_info *info, int op_offset)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k* ext = build_init_op(info, M68K_INS_INVALID, 2, 0);

	switch ((info->ir >> 3) & 3) { // scope
		// Invalid
		case 0:
			d68000_invalid(info);
			return;
			// Line
		case 1:
			MCInst_setOpcode(info->inst, op_offset + 0);
			break;
			// Page
		case 2:
			MCInst_setOpcode(info->inst, op_offset + 1);
			break;
			// All
		case 3:
			ext->op_count = 1;
			MCInst_setOpcode(info->inst, op_offset + 2);
			break;
	}

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->address_mode = M68K_AM_IMMEDIATE;
	op0->type = M68K_OP_IMM;
	op0->imm = (info->ir >> 6) & 3;

	op1->type = M68K_OP_MEM;
	op1->address_mode = M68K_AM_REG_DIRECT_ADDR;
	op1->imm = M68K_REG_A0 + (info->ir & 7);
}