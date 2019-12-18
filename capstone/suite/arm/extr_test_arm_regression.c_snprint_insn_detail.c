#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_1__* detail; } ;
typedef  TYPE_4__ cs_insn ;
struct TYPE_10__ {scalar_t__ type; scalar_t__ value; } ;
struct TYPE_9__ {int scale; int /*<<< orphan*/  disp; scalar_t__ index; scalar_t__ base; } ;
struct TYPE_12__ {TYPE_3__ shift; int /*<<< orphan*/  imm; TYPE_2__ mem; int /*<<< orphan*/  fp; scalar_t__ reg; scalar_t__ type; } ;
typedef  TYPE_5__ cs_arm_op ;
struct TYPE_13__ {int op_count; scalar_t__ cc; scalar_t__ writeback; scalar_t__ update_flags; TYPE_5__* operands; } ;
typedef  TYPE_6__ cs_arm ;
struct TYPE_8__ {TYPE_6__ arm; } ;

/* Variables and functions */
 scalar_t__ ARM_CC_AL ; 
 scalar_t__ ARM_CC_INVALID ; 
#define  ARM_OP_CIMM 133 
#define  ARM_OP_FP 132 
#define  ARM_OP_IMM 131 
#define  ARM_OP_MEM 130 
#define  ARM_OP_PIMM 129 
#define  ARM_OP_REG 128 
 scalar_t__ ARM_SFT_ASR_REG ; 
 scalar_t__ ARM_SFT_INVALID ; 
 scalar_t__ X86_REG_INVALID ; 
 int /*<<< orphan*/  _this_printf (char*,...) ; 
 int /*<<< orphan*/  cs_reg_name (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  handle ; 

__attribute__((used)) static void snprint_insn_detail(char * buf, size_t * cur, size_t * left, cs_insn *ins)
{
	size_t used = 0;

#define _this_printf(...) \
	{ \
		size_t used = 0; \
		used = snprintf(buf + *cur, *left, __VA_ARGS__); \
		*left -= used; \
		*cur += used; \
	}

	cs_arm *arm;
	int i;

	// detail can be NULL on "data" instruction if SKIPDATA option is turned ON
	if (ins->detail == NULL)
		return;

	arm = &(ins->detail->arm);

	if (arm->op_count)
		_this_printf("\top_count: %u\n", arm->op_count);

	for (i = 0; i < arm->op_count; i++) {
		cs_arm_op *op = &(arm->operands[i]);
		switch((int)op->type) {
			default:
				break;
			case ARM_OP_REG:
				_this_printf("\t\toperands[%u].type: REG = %s\n", i, cs_reg_name(handle, op->reg));
				break;
			case ARM_OP_IMM:
				_this_printf("\t\toperands[%u].type: IMM = 0x%x\n", i, op->imm);
				break;
			case ARM_OP_FP:
				_this_printf("\t\toperands[%u].type: FP = %f\n", i, op->fp);
				break;
			case ARM_OP_MEM:
				_this_printf("\t\toperands[%u].type: MEM\n", i);
				if (op->mem.base != X86_REG_INVALID)
					_this_printf("\t\t\toperands[%u].mem.base: REG = %s\n",
							i, cs_reg_name(handle, op->mem.base));
				if (op->mem.index != X86_REG_INVALID)
					_this_printf("\t\t\toperands[%u].mem.index: REG = %s\n",
							i, cs_reg_name(handle, op->mem.index));
				if (op->mem.scale != 1)
					_this_printf("\t\t\toperands[%u].mem.scale: %u\n", i, op->mem.scale);
				if (op->mem.disp != 0)
					_this_printf("\t\t\toperands[%u].mem.disp: 0x%x\n", i, op->mem.disp);

				break;
			case ARM_OP_PIMM:
				_this_printf("\t\toperands[%u].type: P-IMM = %u\n", i, op->imm);
				break;
			case ARM_OP_CIMM:
				_this_printf("\t\toperands[%u].type: C-IMM = %u\n", i, op->imm);
				break;
		}

		if (op->shift.type != ARM_SFT_INVALID && op->shift.value) {
			if (op->shift.type < ARM_SFT_ASR_REG) {
				// shift with constant value
				_this_printf("\t\t\tShift: %u = %u\n", op->shift.type, op->shift.value);
			} else {
				// shift with register
				_this_printf("\t\t\tShift: %u = %s\n", op->shift.type,
						cs_reg_name(handle, op->shift.value));
			}
		}
	}

	if (arm->cc != ARM_CC_AL && arm->cc != ARM_CC_INVALID) {
		_this_printf("\tCode condition: %u\n", arm->cc);
	}

	if (arm->update_flags) {
		_this_printf("\tUpdate-flags: True\n");
	}

	if (arm->writeback) {
		_this_printf("\tWrite-back: True\n");
	}

#undef _this_printf
}