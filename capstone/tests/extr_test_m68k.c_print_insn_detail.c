#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int disp; int scale; int /*<<< orphan*/  index_size; int /*<<< orphan*/  index_reg; int /*<<< orphan*/  base_reg; } ;
struct TYPE_9__ {size_t address_mode; double simm; int register_bits; int /*<<< orphan*/  dimm; TYPE_1__ mem; scalar_t__ imm; int /*<<< orphan*/  reg; scalar_t__ type; } ;
typedef  TYPE_2__ cs_m68k_op ;
struct TYPE_10__ {int op_count; TYPE_2__* operands; } ;
typedef  TYPE_3__ cs_m68k ;
struct TYPE_11__ {TYPE_5__* detail; } ;
typedef  TYPE_4__ cs_insn ;
struct TYPE_12__ {int groups_count; TYPE_3__ m68k; } ;
typedef  TYPE_5__ cs_detail ;

/* Variables and functions */
#define  M68K_OP_FP_DOUBLE 133 
#define  M68K_OP_FP_SINGLE 132 
#define  M68K_OP_IMM 131 
#define  M68K_OP_MEM 130 
#define  M68K_OP_REG 129 
#define  M68K_OP_REG_BITS 128 
 int /*<<< orphan*/  M68K_REG_INVALID ; 
 char* cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  handle ; 
 int /*<<< orphan*/  print_read_write_regs (TYPE_5__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char** s_addressing_modes ; 

__attribute__((used)) static void print_insn_detail(cs_insn *ins)
{
	cs_m68k* m68k;
	cs_detail* detail;
	int i;

	// detail can be NULL on "data" instruction if SKIPDATA option is turned ON
	if (ins->detail == NULL)
		return;

	detail = ins->detail;
	m68k = &detail->m68k;
	if (m68k->op_count)
		printf("\top_count: %u\n", m68k->op_count);

	print_read_write_regs(detail);

	printf("\tgroups_count: %u\n", detail->groups_count);

	for (i = 0; i < m68k->op_count; i++) {
		cs_m68k_op* op = &(m68k->operands[i]);

		switch((int)op->type) {
			default:
				break;
			case M68K_OP_REG:
				printf("\t\toperands[%u].type: REG = %s\n", i, cs_reg_name(handle, op->reg));
				break;
			case M68K_OP_IMM:
				printf("\t\toperands[%u].type: IMM = 0x%x\n", i, (int)op->imm);
				break;
			case M68K_OP_MEM:
				printf("\t\toperands[%u].type: MEM\n", i);
				if (op->mem.base_reg != M68K_REG_INVALID)
					printf("\t\t\toperands[%u].mem.base: REG = %s\n",
							i, cs_reg_name(handle, op->mem.base_reg));
				if (op->mem.index_reg != M68K_REG_INVALID) {
					printf("\t\t\toperands[%u].mem.index: REG = %s\n",
							i, cs_reg_name(handle, op->mem.index_reg));
					printf("\t\t\toperands[%u].mem.index: size = %c\n",
							i, op->mem.index_size ? 'l' : 'w');
				}
				if (op->mem.disp != 0)
					printf("\t\t\toperands[%u].mem.disp: 0x%x\n", i, op->mem.disp);
				if (op->mem.scale != 0)
					printf("\t\t\toperands[%u].mem.scale: %d\n", i, op->mem.scale);

				printf("\t\taddress mode: %s\n", s_addressing_modes[op->address_mode]);
				break;
			case M68K_OP_FP_SINGLE:
				printf("\t\toperands[%u].type: FP_SINGLE\n", i);
				printf("\t\t\toperands[%u].simm: %f\n", i, op->simm);
				break;
			case M68K_OP_FP_DOUBLE:
				printf("\t\toperands[%u].type: FP_DOUBLE\n", i);
				printf("\t\t\toperands[%u].dimm: %lf\n", i, op->dimm);
				break;
			case M68K_OP_REG_BITS:
				printf("\t\toperands[%u].type: REG_BITS = $%x\n", i, op->register_bits);

		}
	}

	printf("\n");
}