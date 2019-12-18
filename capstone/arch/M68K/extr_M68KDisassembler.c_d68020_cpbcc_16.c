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
struct TYPE_11__ {int ir; TYPE_1__* inst; } ;
typedef  TYPE_2__ m68k_info ;
typedef  int /*<<< orphan*/  cs_m68k_op ;
struct TYPE_12__ {int /*<<< orphan*/ * operands; } ;
typedef  TYPE_3__ cs_m68k ;
struct TYPE_10__ {int Opcode; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIMIT_CPU_TYPES (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M68020_PLUS ; 
 int /*<<< orphan*/  M68K_GRP_BRANCH_RELATIVE ; 
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_INS_FBF ; 
 int /*<<< orphan*/  M68K_OP_BR_DISP_SIZE_WORD ; 
 TYPE_3__* build_init_op (TYPE_2__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  make_cpbcc_operand (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  make_int_16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_imm_16 (TYPE_2__*) ; 
 int /*<<< orphan*/  set_insn_group (TYPE_2__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void d68020_cpbcc_16(m68k_info *info)
{
	cs_m68k_op* op0;
	cs_m68k* ext;
	LIMIT_CPU_TYPES(info, M68020_PLUS);

	// these are all in row with the extension so just doing a add here is fine
	info->inst->Opcode += (info->ir & 0x2f);

	ext = build_init_op(info, M68K_INS_FBF, 1, 2);
	op0 = &ext->operands[0];

	make_cpbcc_operand(op0, M68K_OP_BR_DISP_SIZE_WORD, make_int_16(read_imm_16(info)));
	
	set_insn_group(info, M68K_GRP_JUMP);
	set_insn_group(info, M68K_GRP_BRANCH_RELATIVE);
}