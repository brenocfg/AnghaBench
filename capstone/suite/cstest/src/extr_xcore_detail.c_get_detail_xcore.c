#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  csh ;
struct TYPE_8__ {int direct; int /*<<< orphan*/  disp; int /*<<< orphan*/  index; int /*<<< orphan*/  base; } ;
struct TYPE_9__ {TYPE_2__ mem; int /*<<< orphan*/  imm; int /*<<< orphan*/  reg; scalar_t__ type; } ;
typedef  TYPE_3__ cs_xcore_op ;
struct TYPE_10__ {int op_count; TYPE_3__* operands; } ;
typedef  TYPE_4__ cs_xcore ;
typedef  int /*<<< orphan*/  cs_mode ;
struct TYPE_11__ {TYPE_1__* detail; } ;
typedef  TYPE_5__ cs_insn ;
struct TYPE_7__ {TYPE_4__ xcore; } ;

/* Variables and functions */
#define  XCORE_OP_IMM 130 
#define  XCORE_OP_MEM 129 
#define  XCORE_OP_REG 128 
 int /*<<< orphan*/  XCORE_REG_INVALID ; 
 int /*<<< orphan*/  add_str (char**,char*,int,...) ; 
 int /*<<< orphan*/  cs_reg_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 

char *get_detail_xcore(csh *handle, cs_mode mode, cs_insn *ins)
{
	cs_xcore *xcore;
	int i;
	char *result;

	result = (char *)malloc(sizeof(char));
	result[0] = '\0';

	if (ins->detail == NULL)
		return result;

	xcore = &(ins->detail->xcore);
	if (xcore->op_count)
		add_str(&result, " ; op_count: %u", xcore->op_count);

	for (i = 0; i < xcore->op_count; i++) {
		cs_xcore_op *op = &(xcore->operands[i]);
		switch((int)op->type) {
			default:
				break;
			case XCORE_OP_REG:
				add_str(&result, " ; operands[%u].type: REG = %s", i, cs_reg_name(*handle, op->reg));
				break;
			case XCORE_OP_IMM:
				add_str(&result, " ; operands[%u].type: IMM = 0x%x", i, op->imm);
				break;
			case XCORE_OP_MEM:
				add_str(&result, " ; operands[%u].type: MEM", i);
				if (op->mem.base != XCORE_REG_INVALID)
					add_str(&result, " ; operands[%u].mem.base: REG = %s", i, cs_reg_name(*handle, op->mem.base));
				if (op->mem.index != XCORE_REG_INVALID)
					add_str(&result, " ; operands[%u].mem.index: REG = %s", i, cs_reg_name(*handle, op->mem.index));
				if (op->mem.disp != 0)
					add_str(&result, " ; operands[%u].mem.disp: 0x%x", i, op->mem.disp);
				if (op->mem.direct != 1)
					add_str(&result, " ; operands[%u].mem.direct: -1", i);


				break;
		}
	}

	return result;
}