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
struct TYPE_7__ {int ir; } ;
typedef  TYPE_1__ m68k_info ;
struct TYPE_8__ {int imm; scalar_t__ reg; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_9__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_IMMEDIATE ; 
 int /*<<< orphan*/  M68K_AM_REG_DIRECT_DATA ; 
 int /*<<< orphan*/  M68K_INS_MOVEQ ; 
 int /*<<< orphan*/  M68K_OP_IMM ; 
 scalar_t__ M68K_REG_D0 ; 
 TYPE_3__* build_init_op (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68000_moveq(m68k_info *info)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;

	cs_m68k* ext = build_init_op(info, M68K_INS_MOVEQ, 2, 0);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->type = M68K_OP_IMM;
	op0->address_mode = M68K_AM_IMMEDIATE;
	op0->imm = (info->ir & 0xff);

	op1->address_mode = M68K_AM_REG_DIRECT_DATA;
	op1->reg = M68K_REG_D0 + ((info->ir >> 9) & 7);
}