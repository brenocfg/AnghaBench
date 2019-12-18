#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint ;
struct TYPE_13__ {int ir; TYPE_1__* inst; } ;
typedef  TYPE_2__ m68k_info ;
struct TYPE_14__ {scalar_t__ reg; } ;
typedef  TYPE_3__ cs_m68k_op ;
struct TYPE_15__ {TYPE_3__* operands; } ;
typedef  TYPE_4__ cs_m68k ;
struct TYPE_12__ {int Opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_GRP_BRANCH_RELATIVE ; 
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_INS_FDBF ; 
 int /*<<< orphan*/  M68K_OP_BR_DISP_SIZE_WORD ; 
 scalar_t__ M68K_REG_D0 ; 
 TYPE_4__* build_init_op (TYPE_2__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_cpbcc_operand (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ make_int_16 (int) ; 
 int read_imm_16 (TYPE_2__*) ; 
 int /*<<< orphan*/  set_insn_group (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68020_cpdbcc(m68k_info *info)
{
	cs_m68k* ext;
	cs_m68k_op* op0;
	cs_m68k_op* op1;
	uint ext1, ext2;

	LIMIT_CPU_TYPES(info, M68020_PLUS);

	ext1 = read_imm_16(info);
	ext2 = read_imm_16(info);

	// these are all in row with the extension so just doing a add here is fine
	info->inst->Opcode += (ext1 & 0x2f);

	ext = build_init_op(info, M68K_INS_FDBF, 2, 0);
	op0 = &ext->operands[0];
	op1 = &ext->operands[1];

	op0->reg = M68K_REG_D0 + (info->ir & 7);

	make_cpbcc_operand(op1, M68K_OP_BR_DISP_SIZE_WORD, make_int_16(ext2) + 2);

	set_insn_group(info, M68K_GRP_JUMP);
	set_insn_group(info, M68K_GRP_BRANCH_RELATIVE);
}