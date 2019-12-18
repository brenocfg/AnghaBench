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
typedef  int /*<<< orphan*/  m68k_reg ;
typedef  int /*<<< orphan*/  m68k_info ;
struct TYPE_4__ {int imm; int /*<<< orphan*/  reg; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ cs_m68k_op ;
struct TYPE_5__ {TYPE_1__* operands; } ;
typedef  TYPE_2__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_AM_NONE ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 TYPE_2__* build_init_op (int /*<<< orphan*/ *,int,int,int) ; 

__attribute__((used)) static void build_imm_special_reg(m68k_info *info, int opcode, int imm, int size, m68k_reg reg)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k* ext = build_init_op(info, opcode, 2, size);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->type = M68K_OP_IMM;
	op0->address_mode = M68K_AM_IMMEDIATE;
	op0->imm = imm;

	op1->address_mode = M68K_AM_NONE;
	op1->reg = reg;
}