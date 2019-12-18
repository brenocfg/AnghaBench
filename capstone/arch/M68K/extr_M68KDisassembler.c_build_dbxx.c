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
struct TYPE_9__ {int disp; int /*<<< orphan*/  disp_size; } ;
struct TYPE_11__ {TYPE_1__ br_disp; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; scalar_t__ reg; } ;
typedef  TYPE_3__ cs_m68k_op ;
struct TYPE_12__ {TYPE_3__* operands; } ;
typedef  TYPE_4__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_BRANCH_DISPLACEMENT ; 
 int /*<<< orphan*/  M68K_AM_REG_DIRECT_DATA ; 
 int /*<<< orphan*/  M68K_GRP_BRANCH_RELATIVE ; 
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_OP_BR_DISP ; 
 int /*<<< orphan*/  M68K_OP_BR_DISP_SIZE_LONG ; 
 scalar_t__ M68K_REG_D0 ; 
 TYPE_4__* build_init_op (TYPE_2__*,int,int,int) ; 
 int /*<<< orphan*/  set_insn_group (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_dbxx(m68k_info *info, int opcode, int size, int displacement)
{
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	cs_m68k* ext = build_init_op(info, opcode, 2, size);

	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->address_mode = M68K_AM_REG_DIRECT_DATA;
	op0->reg = M68K_REG_D0 + (info->ir & 7);

	op1->type = M68K_OP_BR_DISP;
	op1->address_mode = M68K_AM_BRANCH_DISPLACEMENT;
	op1->br_disp.disp = displacement;
	op1->br_disp.disp_size = M68K_OP_BR_DISP_SIZE_LONG;

	set_insn_group(info, M68K_GRP_JUMP);
	set_insn_group(info, M68K_GRP_BRANCH_RELATIVE);
}