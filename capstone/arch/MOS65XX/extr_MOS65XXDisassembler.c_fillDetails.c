#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  size_t mos65xx_insn ;
typedef  int mos65xx_address_mode ;
struct TYPE_13__ {int am; size_t op_count; TYPE_2__* operands; scalar_t__ modifies_flags; } ;
struct TYPE_14__ {scalar_t__* groups; scalar_t__* regs_read; scalar_t__* regs_write; TYPE_4__ mos65xx; scalar_t__ regs_write_count; scalar_t__ regs_read_count; scalar_t__ groups_count; } ;
typedef  TYPE_5__ cs_detail ;
struct TYPE_17__ {scalar_t__ group_type; scalar_t__ read; scalar_t__ write; scalar_t__ modifies_status; } ;
struct TYPE_16__ {size_t ins; int am; } ;
struct TYPE_15__ {TYPE_3__* Operands; TYPE_1__* flat_insn; } ;
struct TYPE_12__ {int /*<<< orphan*/  ImmVal; } ;
struct TYPE_11__ {int /*<<< orphan*/  mem; int /*<<< orphan*/  type; void* reg; } ;
struct TYPE_10__ {TYPE_5__* detail; } ;
typedef  TYPE_6__ MCInst ;

/* Variables and functions */
 TYPE_9__* InstructionInfoTable ; 
 scalar_t__ MOS65XX_AM_ABSX ; 
 scalar_t__ MOS65XX_AM_ABSY ; 
#define  MOS65XX_AM_ACC 131 
#define  MOS65XX_AM_IMM 130 
#define  MOS65XX_AM_IMP 129 
 scalar_t__ MOS65XX_AM_INDX ; 
 scalar_t__ MOS65XX_AM_INDY ; 
#define  MOS65XX_AM_REL 128 
 scalar_t__ MOS65XX_AM_ZPX ; 
 scalar_t__ MOS65XX_AM_ZPY ; 
 scalar_t__ MOS65XX_GRP_INVALID ; 
 int /*<<< orphan*/  MOS65XX_OP_IMM ; 
 int /*<<< orphan*/  MOS65XX_OP_MEM ; 
 int /*<<< orphan*/  MOS65XX_OP_REG ; 
 void* MOS65XX_REG_ACC ; 
 scalar_t__ MOS65XX_REG_INVALID ; 
 scalar_t__ MOS65XX_REG_P ; 
 scalar_t__ MOS65XX_REG_X ; 
 scalar_t__ MOS65XX_REG_Y ; 
 TYPE_8__* OpInfoTable ; 

__attribute__((used)) static void fillDetails(MCInst *MI, unsigned char opcode)
{
	cs_detail *detail = MI->flat_insn->detail;
	mos65xx_insn ins = OpInfoTable[opcode].ins;
	mos65xx_address_mode am = OpInfoTable[opcode].am;

	detail->mos65xx.am = am;
	detail->mos65xx.modifies_flags = InstructionInfoTable[ins].modifies_status;
	detail->groups_count = 0;
	detail->regs_read_count = 0;
	detail->regs_write_count = 0;
	detail->mos65xx.op_count = 0;

	if (InstructionInfoTable[ins].group_type != MOS65XX_GRP_INVALID) {
		detail->groups[0] = InstructionInfoTable[ins].group_type;
		detail->groups_count++;
	}

	if (InstructionInfoTable[ins].read != MOS65XX_REG_INVALID) {
		detail->regs_read[detail->regs_read_count++] = InstructionInfoTable[ins].read;
	} else if (OpInfoTable[opcode].am == MOS65XX_AM_ACC) {
		detail->regs_read[detail->regs_read_count++] = MOS65XX_REG_ACC;
	} else if (OpInfoTable[opcode].am == MOS65XX_AM_INDY || OpInfoTable[opcode].am == MOS65XX_AM_ABSY || OpInfoTable[opcode].am == MOS65XX_AM_ZPY) {
		detail->regs_read[detail->regs_read_count++] = MOS65XX_REG_Y;
	} else if (OpInfoTable[opcode].am == MOS65XX_AM_INDX || OpInfoTable[opcode].am == MOS65XX_AM_ABSX || OpInfoTable[opcode].am == MOS65XX_AM_ZPX) {
		detail->regs_read[detail->regs_read_count++] = MOS65XX_REG_X;
	}

	if (InstructionInfoTable[ins].write != MOS65XX_REG_INVALID) {
		detail->regs_write[detail->regs_write_count++] = InstructionInfoTable[ins].write;
	} else if (OpInfoTable[opcode].am == MOS65XX_AM_ACC) {
		detail->regs_write[detail->regs_write_count++] = MOS65XX_REG_ACC;
	}

	if (InstructionInfoTable[ins].modifies_status) {
		detail->regs_write[detail->regs_write_count++] = MOS65XX_REG_P;
	}

	switch(am) {
		case MOS65XX_AM_IMP:
		case MOS65XX_AM_REL:
			break;
		case MOS65XX_AM_IMM:
			detail->mos65xx.operands[detail->mos65xx.op_count].type = MOS65XX_OP_IMM;
			detail->mos65xx.operands[detail->mos65xx.op_count].mem = MI->Operands[0].ImmVal;
			detail->mos65xx.op_count++;
			break;
		case MOS65XX_AM_ACC:
			detail->mos65xx.operands[detail->mos65xx.op_count].type = MOS65XX_OP_REG;
			detail->mos65xx.operands[detail->mos65xx.op_count].reg = MOS65XX_REG_ACC;
			detail->mos65xx.op_count++;
			break;
		default:
			detail->mos65xx.operands[detail->mos65xx.op_count].type = MOS65XX_OP_MEM;
			detail->mos65xx.operands[detail->mos65xx.op_count].mem = MI->Operands[0].ImmVal;
			detail->mos65xx.op_count++;
			break;
	}
}