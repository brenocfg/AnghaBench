#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int ir; } ;
typedef  TYPE_2__ m68k_info ;
typedef  scalar_t__ int16_t ;
struct TYPE_9__ {scalar_t__ disp; scalar_t__ base_reg; } ;
struct TYPE_11__ {TYPE_1__ mem; int /*<<< orphan*/  type; int /*<<< orphan*/  address_mode; scalar_t__ reg; } ;
typedef  TYPE_3__ cs_m68k_op ;
struct TYPE_12__ {TYPE_3__* operands; } ;
typedef  TYPE_4__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_REGI_ADDR_DISP ; 
 int /*<<< orphan*/  M68K_INS_MOVEP ; 
 int /*<<< orphan*/  M68K_OP_MEM ; 
 scalar_t__ M68K_REG_A0 ; 
 scalar_t__ M68K_REG_D0 ; 
 TYPE_4__* build_init_op (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ read_imm_16 (TYPE_2__*) ; 

__attribute__((used)) static void build_movep_re(m68k_info *info, int size)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k* ext = build_init_op(info, M68K_INS_MOVEP, 2, size);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->reg = M68K_REG_D0 + ((info->ir >> 9) & 7);

	op1->address_mode = M68K_AM_REGI_ADDR_DISP;
	op1->type = M68K_OP_MEM;
	op1->mem.base_reg = M68K_REG_A0 + (info->ir & 7);
	op1->mem.disp = (int16_t)read_imm_16(info);
}