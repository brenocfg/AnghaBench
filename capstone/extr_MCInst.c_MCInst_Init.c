#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int has_imm; int writeback; char* assembly; scalar_t__ popcode_adjust; scalar_t__ ac_idx; scalar_t__ op1_size; scalar_t__ size; scalar_t__ OpcodePub; scalar_t__ Opcode; TYPE_1__* Operands; } ;
struct TYPE_4__ {int /*<<< orphan*/  Kind; } ;
typedef  TYPE_2__ MCInst ;

/* Variables and functions */
 int /*<<< orphan*/  kInvalid ; 

void MCInst_Init(MCInst *inst)
{
	unsigned int i;

	for (i = 0; i < 48; i++) {
		inst->Operands[i].Kind = kInvalid;
	}

	inst->Opcode = 0;
	inst->OpcodePub = 0;
	inst->size = 0;
	inst->has_imm = false;
	inst->op1_size = 0;
	inst->writeback = false;
	inst->ac_idx = 0;
	inst->popcode_adjust = 0;
	inst->assembly[0] = '\0';
}