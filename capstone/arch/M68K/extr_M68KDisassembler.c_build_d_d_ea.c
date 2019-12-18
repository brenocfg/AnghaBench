#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_10__ {int /*<<< orphan*/  ir; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_11__ {void* reg; void* address_mode; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_12__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 void* M68K_AM_REG_DIRECT_DATA ; 
 void* M68K_REG_D0 ; 
 TYPE_3__* build_init_op (TYPE_1__*,int,int,int) ; 
 int /*<<< orphan*/  get_ea_mode_op (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int read_imm_16 (TYPE_1__*) ; 

__attribute__((used)) static void build_d_d_ea(m68k_info *info, int opcode, int size)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k_op* op2;
	uint extension = read_imm_16(info);
	cs_m68k* ext = build_init_op(info, opcode, 3, size);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];
	op2 = &ext->operands[2];

	op0->address_mode = M68K_AM_REG_DIRECT_DATA;
	op0->reg = M68K_REG_D0 + (extension & 7);

	op1->address_mode = M68K_AM_REG_DIRECT_DATA;
	op1->reg = M68K_REG_D0 + ((extension >> 6) & 7);

	get_ea_mode_op(info, op2, info->ir, size);
}