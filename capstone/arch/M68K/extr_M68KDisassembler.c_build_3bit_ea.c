#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int ir; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_10__ {int /*<<< orphan*/  imm; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_11__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 TYPE_3__* build_init_op (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/ * g_3bit_qdata_table ; 
 int /*<<< orphan*/  get_ea_mode_op (TYPE_1__*,TYPE_2__*,int,int) ; 

__attribute__((used)) static void build_3bit_ea(m68k_info *info, int opcode, int size)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k* ext = build_init_op(info, opcode, 2, size);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->type = M68K_OP_IMM;
	op0->address_mode = M68K_AM_IMMEDIATE;
	op0->imm = g_3bit_qdata_table[(info->ir >> 9) & 7];

	get_ea_mode_op(info, op1, info->ir, size);
}