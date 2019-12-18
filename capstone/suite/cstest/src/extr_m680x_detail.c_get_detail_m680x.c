#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
typedef  int /*<<< orphan*/  cs_mode ;
struct TYPE_12__ {int flags; int offset_bits; int offset; int offset_addr; int /*<<< orphan*/  inc_dec; int /*<<< orphan*/  base_reg; int /*<<< orphan*/  offset_reg; } ;
struct TYPE_11__ {int /*<<< orphan*/  address; } ;
struct TYPE_10__ {int /*<<< orphan*/  address; int /*<<< orphan*/  indirect; } ;
struct TYPE_13__ {scalar_t__ size; size_t access; TYPE_3__ idx; TYPE_2__ rel; TYPE_1__ ext; int /*<<< orphan*/  direct_addr; int /*<<< orphan*/  imm; int /*<<< orphan*/  const_val; int /*<<< orphan*/  reg; scalar_t__ type; } ;
typedef  TYPE_4__ cs_m680x_op ;
struct TYPE_14__ {int op_count; int flags; TYPE_4__* operands; } ;
typedef  TYPE_5__ cs_m680x ;
struct TYPE_15__ {TYPE_7__* detail; } ;
typedef  TYPE_6__ cs_insn ;
struct TYPE_16__ {TYPE_5__ m680x; } ;
typedef  TYPE_7__ cs_detail ;

/* Variables and functions */
 size_t CS_AC_INVALID ; 
 int M680X_FIRST_OP_IN_MNEM ; 
 int M680X_IDX_INDIRECT ; 
 int M680X_IDX_POST_INC_DEC ; 
#define  M680X_OP_CONSTANT 134 
#define  M680X_OP_DIRECT 133 
#define  M680X_OP_EXTENDED 132 
#define  M680X_OP_IMMEDIATE 131 
#define  M680X_OP_INDEXED 130 
#define  M680X_OP_REGISTER 129 
#define  M680X_OP_RELATIVE 128 
 int /*<<< orphan*/  M680X_REG_INVALID ; 
 int /*<<< orphan*/  M680X_REG_PC ; 
 int M680X_SECOND_OP_IN_MNEM ; 
 int /*<<< orphan*/  abs (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_str (char**,char*,...) ; 
 int cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  print_read_write_regs (char*,int /*<<< orphan*/ *,TYPE_7__*) ; 
 int* s_access ; 

char *get_detail_m680x(csh *handle, cs_mode mode, cs_insn *insn)
{
	cs_detail *detail = insn->detail;
	cs_m680x *m680x = NULL;
	int i;
	char *result;

	result = (char *)malloc(sizeof(char));
	result[0] = '\0';

	if (detail == NULL)
		return result;

	m680x = &detail->m680x;

	if (m680x->op_count)
		add_str(&result, " ; op_count: %u", m680x->op_count);

	for (i = 0; i < m680x->op_count; i++) {
		cs_m680x_op *op = &(m680x->operands[i]);
		const char *comment;

		switch ((int)op->type) {
			default:
				break;

			case M680X_OP_REGISTER:
				comment = "";

				if ((i == 0 && m680x->flags & M680X_FIRST_OP_IN_MNEM) ||
						(i == 1 && m680x->flags &
						 M680X_SECOND_OP_IN_MNEM))
					comment = " (in mnemonic)";

				add_str(&result, " ; operands[%u].type: REGISTER = %s%s", i, cs_reg_name(*handle, op->reg), comment);
				break;

			case M680X_OP_CONSTANT:
				add_str(&result, " ; operands[%u].type: CONSTANT = %u", i, op->const_val);
				break;

			case M680X_OP_IMMEDIATE:
				add_str(&result, " ; operands[%u].type: IMMEDIATE = #%d", i, op->imm);
				break;

			case M680X_OP_DIRECT:
				add_str(&result, " ; operands[%u].type: DIRECT = 0x%02X", i, op->direct_addr);
				break;

			case M680X_OP_EXTENDED:
				add_str(&result, " ; operands[%u].type: EXTENDED %s = 0x%04X", i, op->ext.indirect ? "INDIRECT" : "", op->ext.address);
				break;

			case M680X_OP_RELATIVE:
				add_str(&result, " ; operands[%u].type: RELATIVE = 0x%04X", i, op->rel.address);
				break;

			case M680X_OP_INDEXED:
				add_str(&result, " ; operands[%u].type: INDEXED%s", i, (op->idx.flags & M680X_IDX_INDIRECT) ? " INDIRECT" : "");

				if (op->idx.base_reg != M680X_REG_INVALID)
					add_str(&result, " ; base register: %s", cs_reg_name(*handle, op->idx.base_reg));

				if (op->idx.offset_reg != M680X_REG_INVALID)
					add_str(&result, " ; offset register: %s", cs_reg_name(*handle, op->idx.offset_reg));

				if ((op->idx.offset_bits != 0) &&
						(op->idx.offset_reg == M680X_REG_INVALID) &&
						!op->idx.inc_dec) {
					add_str(&result, " ; offset: %d", op->idx.offset);

					if (op->idx.base_reg == M680X_REG_PC)
						add_str(&result, " ; offset address: 0x%X", op->idx.offset_addr);

					add_str(&result, " ; offset bits: %u", op->idx.offset_bits);
				}

				if (op->idx.inc_dec) {
					const char *post_pre = op->idx.flags &
						M680X_IDX_POST_INC_DEC ? "post" : "pre";
					const char *inc_dec = (op->idx.inc_dec > 0) ?
						"increment" : "decrement";

					add_str(&result, " ; %s %s: %d", post_pre, inc_dec, abs(op->idx.inc_dec));
				}

				break;
		}

		if (op->size != 0)
			add_str(&result, " ; size: %u", op->size);

		if (op->access != CS_AC_INVALID)
			add_str(&result, " ; access: %s", s_access[op->access]);
	}

	print_read_write_regs(result, handle, detail);

	return result;
}