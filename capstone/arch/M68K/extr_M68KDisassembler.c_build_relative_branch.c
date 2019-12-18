#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  m68k_info ;
struct TYPE_5__ {int disp; int disp_size; } ;
struct TYPE_6__ {TYPE_1__ br_disp; int /*<<< orphan*/  address_mode; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_7__ {TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;

/* Variables and functions */
 int /*<<< orphan*/  M68K_AM_BRANCH_DISPLACEMENT ; 
 int /*<<< orphan*/  M68K_GRP_BRANCH_RELATIVE ; 
 int /*<<< orphan*/  M68K_GRP_JUMP ; 
 int /*<<< orphan*/  M68K_OP_BR_DISP ; 
 TYPE_3__* build_init_op (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  set_insn_group (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void build_relative_branch(m68k_info *info, int opcode, int size, int displacement)
{
	cs_m68k_op* op;
	cs_m68k* ext = build_init_op(info, opcode, 1, size);

	op = &ext->operands[0];

	op->type = M68K_OP_BR_DISP;
	op->address_mode = M68K_AM_BRANCH_DISPLACEMENT;
	op->br_disp.disp = displacement;
	op->br_disp.disp_size = size;

	set_insn_group(info, M68K_GRP_JUMP);
	set_insn_group(info, M68K_GRP_BRANCH_RELATIVE);
}